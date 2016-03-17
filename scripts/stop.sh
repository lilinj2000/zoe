#!/bin/sh

kill -9 $(ps aux | grep [m]d | awk '{print $2}')

kill -9 $(ps aux | grep [t]ext | awk '{print $2}')

kill -9 $(ps aux | grep [d]b | awk '{print $2}')

kill -9 $(ps aux | grep [f]orwarder | awk '{print $2}')
