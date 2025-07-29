#!/bin/sh

set -e
#---------------------------------------------------------------------- Download WP -----#

curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
chmod +x wp-cli.phar
mv wp-cli.phar /bin/wp
#----------------------------------------------------------------------------------------#

#---------------------------------------------------------------------- ??? -----#
mkdir -p /var/www/wordpress
# Should not be here because of mounted volume (same name)
cd /var/www/wordpress
chmod -R 755 /var/www/wordpress
chown -R www-data:www-data /var/www/wordpress
#----------------------------------------------------------------------------------------#

#------------------------------------------------------------- WP core installation -----#
if [ ! -f wp-config.php ]; then
echo "Downloading Wordpress ..."
wp core download --allow-root
echo "Installing Wordpress ..."
wp core config --dbhost=mariadb:3306 --dbname="${DB_NAME}" \
                --dbuser="${DB_USER}" --dbpass="${DB_PASSWD}" --allow-root
wp core install --url="${DOMAIN_NAME}" --title="${WP_TITLE}" \
                --admin_user="${WP_ADMIN_NAME}" --admin_password="${WP_ADMIN_PASSWD}" \
                --admin_email="${WP_ADMIN_MAIL}" --allow-root
fi
#----------------------------------------------------------------------------------------#

# Configuring fpm to listen to TCP connections
sed -i 's|^listen = .*|listen = 0.0.0.0:9000|' /etc/php81/php-fpm.d/www.conf

mkdir -p /run/php

exec "$@"

#Voir le detail des 3 derniers cmd