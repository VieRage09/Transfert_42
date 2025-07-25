#!/bin/sh

#---------------------------------------------------------------------- Download WP -----#

curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
chmod +x wp-cli.phar
mv wp-cli.phar /bin/wp

#----------------------------------------------------------------------------------------#


#---------------------------------------------------------------------- ??? -----#

cd /var/www/wordpress
chmod -R 755 var/www/wordpress
# chown -R www-data:www-data /var/www/wordpress
# --> Il faut creer le groupe pour que ca fonctionne -> A voir

#----------------------------------------------------------------------------------------#


#------------------------------------------------------------- WP core installation -----#
# wp core download 
wp --info
wp core download
wp core config --dbhost=mariadb:3306 --dbname="$DB_NAME" --dbuser"$DB_USER" --dbpass="$DB_PASSWD"
wp core install --url="$DOMAIN_NAME" 

#----------------------------------------------------------------------------------------#
