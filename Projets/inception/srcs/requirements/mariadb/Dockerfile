FROM debian:12.10

WORKDIR /app

RUN apt-get update && apt-get upgrade -y &&\
    apt-get install -y mariadb-server netcat-openbsd bash

COPY db_conf.sh .

RUN chmod +x db_conf.sh && rm -rf /var/lib/mysql/*

EXPOSE 3306

ENTRYPOINT ["./db_conf.sh"]

