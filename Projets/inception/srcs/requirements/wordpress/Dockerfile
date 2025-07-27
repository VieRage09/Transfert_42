FROM alpine:3.18

WORKDIR /app

RUN apk update && apk upgrade &&\
    apk add curl php php-phar php-curl php-fpm php81-mysqli mariadb-client 
#php-phar might be optional

# Increase base php memory for downloading wordpress cli core
RUN echo "memory_limit = 512M" > /etc/php81/conf.d/99-memory.ini

COPY wp_conf.sh .

RUN chmod +x wp_conf.sh

ENTRYPOINT ["./wp_conf.sh"]