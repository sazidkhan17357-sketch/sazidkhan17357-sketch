# Centralized Log Management Using Graylog

This is my academic project on collecting Linux logs in one place and making them easier to search. I worked with this setup in a Kali Linux virtual machine using VirtualBox.

The idea is straightforward: instead of checking logs separately on each machine, send them to a central Graylog instance.

## Tools used

- **Kali Linux:** the operating system for the lab
- **Graylog:** receives logs and provides the search interface
- **MongoDB:** stores Graylog configuration and metadata
- **OpenSearch:** indexes log data so it can be searched
- **rsyslog:** forwards log messages from the source system
- **VirtualBox:** runs the Linux lab environment

## How the parts fit together

1. Linux creates system or application log messages.
2. rsyslog forwards selected messages to Graylog.
3. Graylog receives and processes the incoming events.
4. OpenSearch indexes the events.
5. MongoDB stores Graylog's configuration and metadata.
6. I can then search and review the events in the Graylog interface.

## Lab steps

1. Set up the Kali Linux virtual machine.
2. Install and configure the services needed by Graylog.
3. Create a Graylog input for incoming log messages.
4. Configure rsyslog to forward logs.
5. Generate a few test events.
6. Check whether the events arrive and can be found in Graylog.

## What I learned

This project gave me practice with Linux services, configuration files, log forwarding, and the roles of the different components in a centralized logging setup. It also introduced me to troubleshooting services that do not start as expected.

## Current state of this repository

This README describes the project and its intended lab workflow. It is not yet a complete, ready-to-deploy installation guide. I still need to add the configuration files, screenshots and test results from my own working setup as I verify them.

## Safety

Only collect logs from systems you own or have permission to monitor. Remove private IP addresses, usernames, hostnames, tokens and other sensitive details before sharing screenshots.
