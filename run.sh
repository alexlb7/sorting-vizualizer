#!/bin/bash
# source envs.sh
python3 /api/manage.py migrate --no-input

python3 /api/manage.py collectstatic --no-input

gunicorn api.wsgi:application --bind 0.0.0.0:8000