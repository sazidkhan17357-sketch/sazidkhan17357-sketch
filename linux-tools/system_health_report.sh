#!/usr/bin/env bash
set -euo pipefail

if [[ "$(uname -s)" != "Linux" ]]; then
    printf 'This script is intended for Linux systems.\n' >&2
    exit 1
fi

printf 'Linux System Health Report\n'
printf '%s\n' '=========================='
printf 'Hostname: %s\n' "$(hostname)"
printf 'Kernel:   %s\n' "$(uname -r)"
printf 'Time:     %s\n' "$(date)"
printf '\n'

printf 'Uptime and load\n'
printf '%s\n' '---------------'
uptime
printf '\n'

printf 'Memory (from /proc/meminfo)\n'
printf '%s\n' '---------------------------'
awk '
    /^MemTotal:/ { total = $2 }
    /^MemAvailable:/ { available = $2 }
    END {
        if (total > 0) {
            used = total - available
            printf "Total:     %.2f GiB\n", total / 1048576
            printf "Available: %.2f GiB\n", available / 1048576
            printf "Used:      %.2f GiB (%.1f%%)\n", used / 1048576, used * 100 / total
        } else {
            print "Memory information unavailable."
        }
    }
' /proc/meminfo
printf '\n'

printf 'Filesystem usage\n'
printf '%s\n' '----------------'
df -h -x tmpfs -x devtmpfs
printf '\n'

printf 'Top processes by CPU usage\n'
printf '%s\n' '--------------------------'
ps -eo pid,comm,%cpu,%mem --sort=-%cpu | head -n 6
