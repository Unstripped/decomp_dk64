#!/usr/bin/env bash
set -e

# Cleanup on exit
cleanup() {
    echo "[entrypoint] Stopping emulator services..."
    kill -TERM "$ARES_PID" 2>/dev/null || true
    kill -TERM "$VNC_PID" 2>/dev/null || true
    kill -TERM "$XVFB_PID" 2>/dev/null || true
    wait "$ARES_PID" 2>/dev/null || true
    exit 0
}

trap cleanup SIGTERM SIGINT

# Default ROM discovery
ROM="${ROM_PATH:-}"
SAVE_SLOT="${SAVE_STATE_SLOT:-}"
VNC_PASS="${VNC_PASSWORD:-dk64}"
DEBUG_PORT="${DEBUG_PORT:-9123}"
SESSION_NAME="${SESSION_NAME:-main}"
SAVE_PATH="${SAVE_PATH:-/dk64/emu/sessions/${SESSION_NAME}/states/}"

# Parse CLI arguments if passed
while [[ $# -gt 0 ]]; do
    case "$1" in
        --save-state|--slot)
            SAVE_SLOT="$2"
            shift 2
            ;;
        --save-path)
            SAVE_PATH="$2"
            shift 2
            ;;
        --session|--name)
            SESSION_NAME="$2"
            SAVE_PATH="/dk64/emu/sessions/${SESSION_NAME}/states/"
            shift 2
            ;;
        --vnc-password)
            VNC_PASS="$2"
            shift 2
            ;;
        --debug-port)
            DEBUG_PORT="$2"
            shift 2
            ;;
        -*)
            echo "Unknown option: $1" >&2
            shift
            ;;
        *)
            if [[ -z "$ROM" ]]; then
                ROM="$1"
            fi
            shift
            ;;
    esac
done

if [[ -z "$ROM" ]]; then
    if [[ -f "/dk64/baserom.us.z64" ]]; then
        ROM="/dk64/baserom.us.z64"
    elif [[ -f "/dk64/build/dk64.us.z64" ]]; then
        ROM="/dk64/build/dk64.us.z64"
    else
        echo "Error: No ROM found at /dk64/baserom.us.z64 or /dk64/build/dk64.us.z64" >&2
        exit 1
    fi
fi

echo "[entrypoint] Starting DK64 Emulator session..."
echo "[entrypoint] ROM: $ROM"
echo "[entrypoint] GDB remote port: $DEBUG_PORT"
echo "[entrypoint] VNC password: $VNC_PASS"

# Ensure runtime directories exist
mkdir -p /root/.local/share/ares-imgui
[[ "$SAVE_PATH" != */ ]] && SAVE_PATH="${SAVE_PATH}/"
mkdir -p "$SAVE_PATH" /dk64/emu/screenshots /dk64/emu/logs
if [[ ! -e "$SAVE_PATH/Nintendo 64" && ! -L "$SAVE_PATH/Nintendo 64" ]]; then
    ln -s . "$SAVE_PATH/Nintendo 64" 2>/dev/null || true
fi

if [[ ! -f "/root/.local/share/ares-imgui/settings.bml" ]]; then
    cp /opt/emu/default_settings.bml /root/.local/share/ares-imgui/settings.bml
fi

# 1. Start Xvfb (Virtual X11 Display)
export DISPLAY=:99
Xvfb :99 -screen 0 1280x720x24 -ac +extension GLX +render -noreset &
XVFB_PID=$!

# Wait for X server to be ready
echo "[entrypoint] Waiting for Xvfb..."
for i in {1..50}; do
    if xset -q -display :99 >/dev/null 2>&1 || [[ -e /tmp/.X11-unix/X99 ]]; then
        break
    fi
    sleep 0.1
done

# 2. Start x11vnc
echo "[entrypoint] Starting x11vnc..."
x11vnc -display :99 -forever -shared -rfbport 5900 -passwd "$VNC_PASS" -noxdamage -bg 2>&1 | tee /dk64/emu/logs/x11vnc.log &
VNC_PID=$!

# 3. Start ares
ARES_CMD=(
    ares
    --setting "Developer/DebugServerEnabled=true"
    --setting "Developer/DebugServerPort=$DEBUG_PORT"
    --setting "Developer/DebugServerUseIPv4=true"
    --setting "Nintendo64/ExpansionPak=true"
    --setting "Input/Defocus=Allow"
    --setting "Video/Renderer=angrylion"
    --setting "Paths/Saves=${SAVE_PATH}"
    --setting "Paths/Screenshots=/dk64/emu/screenshots"
    --play-mode
    --no-file-prompt
)

if [[ -n "$SAVE_SLOT" ]]; then
    ARES_CMD+=(--save-state "$SAVE_SLOT")
fi

ARES_CMD+=("$ROM")

echo "[entrypoint] Launching ares..."
"${ARES_CMD[@]}" &
ARES_PID=$!

# Wait for ares to terminate
wait "$ARES_PID"
