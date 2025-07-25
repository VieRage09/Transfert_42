FROM debian:bookworm

WORKDIR /app

RUN apt-get update && apt-get upgrade -y &&\
    apt-get install mariadb-server -y
COPY db_conf.sh .
RUN chmod +x db_conf.sh

ENTRYPOINT ["./db_conf.sh"]

