import * as fs from "node:fs";
import * as path from "node:path";
import type { ExtensionAPI } from "@oh-my-pi/pi-coding-agent";

// Applies `.scratch/routes/<agent>.json` written by `tools/ledger.py route`; logs to drafts/spawns.jsonl.
const MAX_AGE_MS = 6 * 3600 * 1000;

function stamp(): string {
	return new Date().toISOString().replace(/\.\d{3}Z$/, "Z");
}

export default function decompRouter(pi: ExtensionAPI) {
	pi.setLabel("dk64 decomp router");
	pi.on("before_subagent_spawn", async (event, ctx) => {
		if (!event.spawnKey) return;
		const key = event.spawnKey.split(".").pop() as string;
		const dup = /^(.+)-\d+$/.exec(key);
		const names = dup ? [key, dup[1]] : [key];
		const log = path.join(ctx.cwd, "drafts", "spawns.jsonl");
		// Every spawn is logged: an unrouted marker (model null) stops `ledger.py record` from
		// attributing an earlier routed spawn of the same name to this invocation.
		const unrouted = () => {
			const entry = {
				ts: stamp(), spawn_key: event.spawnKey, agent: names[names.length - 1], agent_type: event.agent,
				invocation: event.invocationKind, tier: null, model: null, forced: false, functions: [],
			};
			fs.appendFileSync(log, `${JSON.stringify(entry)}\n`);
		};
		const dir = path.join(ctx.cwd, ".scratch", "routes");
		const file = process.env.DK64_ROUTER === "off"
			? undefined
			: names.map(n => path.join(dir, `${n}.json`)).find(f => fs.existsSync(f));
		try {
			if (!file) {
				unrouted();
				return;
			}
			const route = JSON.parse(fs.readFileSync(file, "utf8"));
			if (Date.now() - Date.parse(route.created) > MAX_AGE_MS) {
				fs.unlinkSync(file);
				unrouted();
				return;
			}
			const entry = {
				ts: stamp(), spawn_key: event.spawnKey, agent: route.agent, agent_type: event.agent,
				invocation: event.invocationKind, tier: route.tier, model: route.model, forced: route.forced,
				functions: route.functions,
			};
			fs.appendFileSync(log, `${JSON.stringify(entry)}\n`);
			fs.unlinkSync(file);
			return { model: route.model, note: `dk64 router: ${route.note}` };
		} catch (err) {
			return { block: true, reason: `decomp-router: ${file ?? log}: ${err instanceof Error ? err.message : String(err)}` };
		}
	});
}
