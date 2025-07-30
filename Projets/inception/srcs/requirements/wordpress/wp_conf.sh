#!/bin/sh

# Strict mode: exits as sound as an error occurs
set -e

#---------------------------------------------------------------------- Download WP -----#
if [ ! -f /bin/wp ]; then
    echo "Downloading WP_CLI..."
    curl -SL -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
    chmod +x wp-cli.phar
    mv wp-cli.phar /bin/wp
else
    echo "WP_CLI already present, skipping download"
fi
#----------------------------------------------------------------------------------------#

#------------------------------------------------- Granting permissions & ownership -----#
mkdir -p /var/www/wordpress
# Should not be here because of mounted volume (same name)
cd /var/www/wordpress
chmod -R 755 /var/www/wordpress
chown -R www-data:www-data /var/www/wordpress
#----------------------------------------------------------------------------------------#

#------------------------------------------------------------- WP core installation -----#
if [ ! -f wp-config.php ]; then
    echo "Downloading Wordpress core..."
    wp core download --allow-root
    echo "Setting up Wordpress..."
    wp core config  --dbhost=mariadb:3306 --dbname="${DB_NAME}" \
                    --dbuser="${DB_USER}" --dbpass="${DB_PASSWD}" --allow-root
    echo "Installing Wordpress..."
    wp core install --url="${DOMAIN_NAME}" --title="${WP_TITLE}" \
                    --admin_user="${WP_ADMIN_NAME}" \
                    --admin_password="${WP_ADMIN_PASSWD}" \
                    --admin_email="${WP_ADMIN_MAIL}" --allow-root
    wp user create  "${WP_USER_NAME}" "${WP_USER_MAIL}" \
                    --user_pass="${WP_USER_PASSWD}" --role="${WP_USER_ROLE}" --allow-root
    echo "Wordpress installation completed !"
else
    echo "Wordpress already configured, skipping setup"
fi
#----------------------------------------------------------------------------------------#

# Configuring fpm to listen to TCP connections
sed -i 's|^listen = .*|listen = 0.0.0.0:9000|' /etc/php81/php-fpm.d/www.conf

mkdir -p /run/php
#WHY ?

echo "Launching php-fpm process"

exec "$@"
