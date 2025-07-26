#!/bin/sh

#---------------------------------------------------------------------- Download WP -----#

curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
chmod +x wp-cli.phar
mv wp-cli.phar /bin/wp

#----------------------------------------------------------------------------------------#


#---------------------------------------------------------------------- ??? -----#
adduser -u 82 -D -S -G www-data www-data

mkdir -p /var/www/wordpress
cd /var/www/wordpress
chmod -R 755 /var/www/wordpress
chown -R www-data:www-data /var/www/wordpress
#----------------------------------------------------------------------------------------#


#------------------------------------------------------------- WP core installation -----#
# wp core download 
wp core download --allow-root
wp core config  --dbhost=mariadb:3306 --dbname="$DB_NAME" \
                --dbuser="$DB_USER" --dbpass="$DB_PASSWD" --allow-root
wp core install --url="$DOMAIN_NAME" --title="$WP_TITLE" \
                --admin_user="$WP_ADMIN_NAME" --admin_password="$WP_ADMIN_PASSWD" \
                --admin_email="$WP_ADMIN_MAIL" --allow-root

#----------------------------------------------------------------------------------------#
