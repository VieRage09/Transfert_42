#!/bin/sh

# Strict mode: exits as sound as an error occurs
set -e

# Reading environment variables from secrets
DB_PASSWD=$(cat /run/secrets/db_passwd)
WP_ADMIN_PASSWD=$(cat /run/secrets/wp_admin_passwd)
WP_USER_PASSWD=$(cat /run/secrets/wp_user_passwd)

#---------------------------------------------------------------------- Download WP -----#
echo "========== Wordpress: Container started =========="

if [ ! -f /bin/wp ]; then
    echo "========== Wordpress: Downloading WP_CLI =========="
    curl -SL -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
    chmod +x wp-cli.phar
    mv wp-cli.phar /bin/wp
else
    echo "========== Wordpress: WP_CLI already there =========="
fi
#----------------------------------------------------------------------------------------#

#------------------------------------------------- Granting permissions & ownership -----#
mkdir -p /var/www/wordpress
# Should not be here because of mounted volume (same name)
echo "========== Wordpress: Setting permissions & ownership for /var/www/wordpress =========="
cd /var/www/wordpress
chmod -R 755 /var/www/wordpress
chown -R www-data:www-data /var/www/wordpress
#----------------------------------------------------------------------------------------#

echo "========== Wordpress: Waiting for MariaDB to be ready =========="
until mysqladmin ping -h mariadb -u "${DB_USER}" -p"${DB_PASSWD}" --silent; do
    echo "..."
    sleep 1
done

#------------------------------------------------------------- WP core installation -----#
if [ ! -f wp-config.php ]; then
    echo "========== Wordpress: Downloading core =========="
    wp core download --allow-root
    echo "========== Wordpress: Configuring wp-config.php =========="
    wp core config  --dbhost=mariadb --dbname="${DB_NAME}" \
                    --dbuser="${DB_USER}" --dbpass="${DB_PASSWD}" --allow-root
    echo "========== Wordpress: Installing core =========="
    wp core install --url="${DOMAIN_NAME}" --title="${WP_TITLE}" \
                    --admin_user="${WP_ADMIN_NAME}" \
                    --admin_password="${WP_ADMIN_PASSWD}" \
                    --admin_email="${WP_ADMIN_MAIL}" --allow-root
    wp user create  "${WP_USER_NAME}" "${WP_USER_MAIL}" \
                    --user_pass="${WP_USER_PASSWD}" --role="${WP_USER_ROLE}" --allow-root
    echo "========== Wordpress: installation completed! =========="
else
    echo "========== Wordpress: already configured, skipping setup =========="
fi
#----------------------------------------------------------------------------------------#

# Configuring fpm to listen to TCP connections
sed -i 's|^listen = .*|listen = 0.0.0.0:9000|' /etc/php81/php-fpm.d/www.conf

# Needed for PHP-FPM socket files
mkdir -p /run/php

echo "========== Wordpress: Launching PHP-FPM Daemon =========="

exec "$@"
