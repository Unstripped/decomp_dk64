set pagination off
set confirm off
set breakpoint always-inserted off
awatch *(char*)0x807fb603
awatch *(char*)0x807fb600
python

import gdb, time, re, threading
labels={1: 'D_807FB603', 2: 'gCollisionResolvePass'}
meta={1: (2155853315, 1), 2: (2155853312, 1)}
last=[]
done=[False]
def on_stop(ev):
    global last
    last=[b.number for b in getattr(ev,'breakpoints',[])]
gdb.events.stop.connect(on_stop)
def stopper():
    done[0]=True
    gdb.post_event(lambda: gdb.execute('interrupt'))
threading.Timer(50, stopper).start()
counts={}
inf=gdb.selected_inferior()
def val(n):
    a,s=meta[n]
    b=bytes(inf.read_memory(a,s))
    return b.hex()
for i in range(100000):
    if done[0]: break
    last=[]
    try:
        s=gdb.execute('continue', to_string=True)
    except Exception as e:
        print('ERR',e); break
    if done[0] and not last: break
    pc=int(gdb.parse_and_eval('$pc'))&0xffffffff
    sym=gdb.execute('info symbol $pc', to_string=True).strip().split(' in section')[0]
    rsym=gdb.execute('info symbol $ra', to_string=True).strip().split(' in section')[0]
    vs=[(labels.get(n,n), val(n)) for n in last if n in meta]
    key=(tuple(labels.get(n,n) for n in last), sym, tuple(v for _,v in vs))
    counts[key]=counts.get(key,0)+1
    if counts[key]<=2:
        print('HIT', vs, hex(pc), sym, '| ra', rsym, flush=True)
    gdb.execute('disable', to_string=True)
    gdb.execute('stepi', to_string=True)
    gdb.execute('enable', to_string=True)
for k,v in counts.items(): print('COUNT', k, v)
print('TOTAL', sum(counts.values()))
gdb.execute('delete', to_string=True)
gdb.execute('detach', to_string=True)

end
quit
