FROM debian:bookworm

RUN apt update && apt upgrade -y &&\
    apt install mariadb-server -y

WORKDIR /app
COPY db_conf.sh .
RUN chmod +x db_conf.sh

ENV DB_NAME=MDB_Inception \
    DB_USER=Tom \
    DB_PASSWD=password

ENTRYPOINT ["./db_conf.sh"]

