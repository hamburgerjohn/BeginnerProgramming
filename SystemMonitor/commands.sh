#!/bin/bash
nvidia-smi --query-gpu=temperature.gpu --format=csv,noheader
nvidia-smi --query-gpu=utilization.gpu --format=csv,noheader
sensors -A | grep temp1:*
mpstat -P ALL | cut -c 13-
free -m


