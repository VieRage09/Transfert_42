FROM alpine:3.19

WORKDIR /app

RUN apk update && apk upgrade &&\
    apk add nginx openssl

RUN mkdir -p /etc/nginx/ssl && openssl req -x509 -nodes \
    -out /etc/nginx/ssl/inception.crt                   \
    -keyout /etc/nginx/ssl/inception.key                \
    -subj "/C=FR/ST=IDF/L=Paris/O=42/OU=42Paris/CN=$DOMAIN_NAME/UID=root" 

COPY nginx.conf /etc/nginx/nginx.conf

RUN mkdir -p /var/www/wordpress

ENTRYPOINT ["nginx", "-g", "daemon off;"]