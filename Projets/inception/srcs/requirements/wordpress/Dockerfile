FROM alpine:3.18

WORKDIR /app

RUN apk update && apk upgrade &&\
    apk add curl php81 php81-phar php81-mbstring php81-curl php81-fpm php81-mysqli \ 
    mariadb-client netcat-openbsd
# netcat used for healthcheck

# Increase base php memory for downloading wordpress cli core and make it executable
RUN echo "memory_limit = 512M" > /etc/php81/conf.d/99-memory.ini && \
    curl -SL -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar && \
    chmod +x wp-cli.phar && \
    mv wp-cli.phar /bin/wp

COPY wp_conf.sh .

RUN chmod +x wp_conf.sh && \
    adduser -u 82 -D -S -G www-data www-data

ENTRYPOINT ["./wp_conf.sh"]
CMD ["php-fpm81", "-F"]