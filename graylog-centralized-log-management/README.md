# Centralized Log Management Using Graylog

**Academic project | Linux | Graylog | MongoDB | OpenSearch | rsyslog**

## Overview

This project explores centralized collection and analysis of system logs using Graylog in a Kali Linux / VirtualBox lab environment. Instead of checking logs on each machine separately, a centralized log-management setup provides one place to search and monitor incoming events.

## Technologies

- **Kali Linux** – lab operating system
- **Graylog** – log collection, search, and dashboard interface
- **MongoDB** – Graylog configuration and metadata storage
- **OpenSearch** – log indexing and search backend
- **rsyslog** – log forwarding

## High-level architecture

1. A Linux system generates system/application log messages.
2. rsyslog forwards configured messages to the Graylog input.
3. Graylog receives and processes the events.
4. OpenSearch indexes the log data for searching.
5. MongoDB stores Graylog metadata and configuration.
6. The user searches and reviews events in the Graylog web interface.

## Lab workflow

1. Prepare a Kali Linux virtual machine.
2. Install and configure the required backend services.
3. Configure Graylog and create an input for incoming logs.
4. Configure rsyslog forwarding on the log source.
5. Generate test log events.
6. Verify that events arrive and can be searched in Graylog.

## Learning outcomes

- Understanding centralized logging concepts
- Working with Linux services and configuration
- Exploring log forwarding and ingestion
- Understanding the roles of MongoDB and OpenSearch
- Troubleshooting service and connectivity issues

## Project status

Academic lab project documentation. Add your own screenshots, configuration files, test results, and troubleshooting notes as you verify each step in your environment.

## Safety

Use only systems and log data you own or are authorized to monitor. Remove hostnames, IP addresses, usernames, tokens, and other sensitive details from screenshots before publishing.