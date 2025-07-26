FROM debian:12.10

WORKDIR /app

RUN apt-get update && apt-get upgrade -y &&\
    apt-get install -y mariadb-server netcat-openbsd
COPY db_conf.sh .
RUN chmod +x db_conf.sh

ENTRYPOINT ["./db_conf.sh"]

