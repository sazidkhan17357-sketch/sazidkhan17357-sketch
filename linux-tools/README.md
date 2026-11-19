# Linux System Health Report

This Bash script prints a quick overview of a Linux machine. I made it as a small way to practise shell scripting and learn where Linux exposes useful system information.

## What it shows

- Hostname and kernel version
- Current date and time
- System uptime and load averages
- Total, available and used memory
- Disk space by filesystem
- The five processes using the most CPU

## Requirements

- Linux
- Bash
- Common command-line tools: awk, df, head, hostname, ps, uname and uptime

## Run it

From the root of this repository:

~~~bash
bash linux-tools/system_health_report.sh
~~~

Or make the script executable first:

~~~bash
chmod +x linux-tools/system_health_report.sh
./linux-tools/system_health_report.sh
~~~

The script only reads system information. It does not install anything or change system settings, and it does not need root access.

## What I practised

Bash scripting, pipes, process inspection, disk and memory checks, using awk, and reading information from /proc/meminfo.
