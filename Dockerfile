FROM python:3.10.5-slim-buster

RUN apt-get update
RUN apt-get install g++ -y

RUN pip install --upgrade pip

COPY ./requirements.txt .
RUN pip install -r requirements.txt

COPY ./api /api
WORKDIR /api


COPY ./run.sh /
ENTRYPOINT ["sh","/run.sh"]