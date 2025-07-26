FROM alpine:3.18

WORKDIR /app

RUN apk update && apk upgrade &&\
    apk add nginx openssl

RUN mkdir -p /etc/nginx/ssl && openssl req -x509 -nodes \
    -out /etc/nginx/ssl/inception.crt                   \
    -keyout /etc/nginx/ssl/inception.key                \
    -subj "/C=FR/ST=IDF/L=Paris/O=42/OU=42Paris/CN=$DOMAIN_NAME/UID=root" 

COPY nginx.conf /etc/nginx/nginx.conf

RUN mkdir -p /var/www/wordpress

# RUN chown -R www-data:www-data /var/www/wordpress
# A creer si important --> Alpine n'a pas ce grp la par defaut

ENTRYPOINT ["nginx", "-g", "daemon off;"]