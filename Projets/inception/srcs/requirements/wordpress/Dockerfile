FROM alpine:3.18

WORKDIR /app

RUN apk update && apk upgrade &&\
    apk add curl php81 php81-phar php81-curl php81-fpm php81-mysqli mariadb-client 
#php-phar might be optional

# Increase base php memory for downloading wordpress cli core
RUN echo "memory_limit = 512M" > /etc/php81/conf.d/99-memory.ini

COPY wp_conf.sh .

RUN chmod +x wp_conf.sh &&\
    adduser -u 82 -D -S -G www-data www-data

ENTRYPOINT ["./wp_conf.sh"]
CMD ["php81-fpm", "-F"]