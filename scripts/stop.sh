#!/bin/sh

kill -9 $(ps aux | grep [m]d | awk '{print $2}')

kill -9 $(ps aux | grep [t]ext | awk '{print $2}')

kill -9 $(ps aux | grep [p]roxy | awk '{print $2}')
