#!/usr/bin/env bash
set -eu

ROOT_DIR=$(cd "$(dirname "$0")/../../.." && pwd)
FR_DIR="$ROOT_DIR/SDK_embedded/libs/FreeRTOS"
SRC_DIR="$FR_DIR/Source"
TMP_DIR=$(mktemp -d)
trap 'rm -rf "$TMP_DIR"' EXIT

TARGET_TAG="V10.4.6"
ARCHIVE_URL="https://github.com/FreeRTOS/FreeRTOS-Kernel/archive/refs/tags/${TARGET_TAG}.tar.gz"

if ! command -v curl >/dev/null 2>&1; then
  echo "curl is required to download the upstream FreeRTOS source" >&2
  exit 1
fi

mkdir -p "$SRC_DIR/portable/GCC"

curl -L --fail -o "$TMP_DIR/freertos.tar.gz" "$ARCHIVE_URL"
tar -xzf "$TMP_DIR/freertos.tar.gz" -C "$TMP_DIR"
UPSTREAM_DIR="$TMP_DIR/FreeRTOS-Kernel-10.4.6"

cp "$UPSTREAM_DIR"/list.c "$SRC_DIR"/
cp "$UPSTREAM_DIR"/queue.c "$SRC_DIR"/
cp "$UPSTREAM_DIR"/tasks.c "$SRC_DIR"/
cp "$UPSTREAM_DIR"/timers.c "$SRC_DIR"/
cp "$UPSTREAM_DIR"/stream_buffer.c "$SRC_DIR"/
cp "$UPSTREAM_DIR"/event_groups.c "$SRC_DIR"/
cp "$UPSTREAM_DIR"/croutine.c "$SRC_DIR"/

rm -rf "$SRC_DIR/include"
cp -R "$UPSTREAM_DIR/include" "$SRC_DIR/include"

rm -rf "$SRC_DIR/portable/GCC/ARM_CM4F"
cp -R "$UPSTREAM_DIR/portable/GCC/ARM_CM4F" "$SRC_DIR/portable/GCC/ARM_CM4F"

cat > "$FR_DIR/UPGRADE_10_4_X_NOTES.txt" <<'EOF'
FreeRTOS safe minimal upgrade plan
=================================

Target kernel: FreeRTOS Kernel 10.4.6
Source: https://github.com/FreeRTOS/FreeRTOS-Kernel/tree/V10.4.6

Why this version:
- same major line as the current SDK (10.x)
- lower migration risk than jumping directly to 11/12
- keeps the project-specific ARM CM4F port compatible with the existing firmware setup

Required compatibility checks before final firmware build:
1. Keep configUSE_KLIBC_REENTRANT and the custom reentrant glue from the project.
2. Preserve the custom freertos_tasks_c_additions_init hook used by stdimpl.cc.
3. Verify the GCC ARM_CM4F port macros still match the board interrupts / NVIC priorities.
4. Rebuild the firmware and fix any API or config warnings after the kernel swap.

This repository keeps the project-specific FreeRTOSConfig.h in the app tree.
The upstream kernel alone is not enough; the project config must still be validated against the new kernel.
EOF

echo "FreeRTOS 10.4.6 staged into $SRC_DIR"
echo "Next steps: rebuild the ARM firmware and validate the custom kernel hooks and reentrant support."
