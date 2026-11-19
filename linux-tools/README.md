# Linux System Health Report

A small Bash utility that prints a quick snapshot of a Linux machine's health using standard system commands and the Linux `/proc` filesystem.

## Features

- Hostname, kernel version, and current date/time
- Uptime and load averages
- Total, available, and used memory
- Filesystem usage
- Top five processes by CPU usage

## Requirements

- Linux
- Bash
- Standard utilities: `awk`, `df`, `head`, `hostname`, `ps`, `uname`, and `uptime`

## Run

From the repository root:

```bash
bash linux-tools/system_health_report.sh
```

Or make it executable and run it:

```bash
chmod +x linux-tools/system_health_report.sh
./linux-tools/system_health_report.sh
```

The script only reads system information. It does not install packages, change system settings, or require root privileges.

## Concepts demonstrated

Bash scripting, command pipelines, process inspection, filesystem monitoring, text processing with `awk`, and reading Linux system information from `/proc/meminfo`.
