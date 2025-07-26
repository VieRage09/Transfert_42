FROM alpine:3.18

WORKDIR /app

RUN apk update && apk upgrade &&\
    apk add curl php php-phar php-fpm mariadb-client 
#php-phar might be optional

COPY wp_conf.sh .

RUN chmod +x wp_conf.sh

ENTRYPOINT ["./wp_conf.sh"]