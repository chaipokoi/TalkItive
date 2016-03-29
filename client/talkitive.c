#include "talkitive.h"

int talkitive_search(usbmuxd_device_info_t **list)
{
	int res = usbmuxd_get_device_list(list);
	if(res < 0)
	{
		printf("Veuillez lancer le service usbmuxd\n");
		exit(1);
	}
	printf("Appareils trouvé: %d\n", res);
	return res;
}

int talkitive_get_device(usbmuxd_device_info_t *device)
{
	int res = usbmuxd_get_device_by_udid(device->udid, device);
	if(res < 0)
	{
		printf("Veuillez lancer le service usbmuxd\n");
		exit(1);
	}
	printf("Reception des informations..OK\n");
	return res;
}

int talkitive_connect(usbmuxd_device_info_t *device, const unsigned short port)
{
	int res = usbmuxd_connect(device->handle, port);
	if(res < 0)
	{
		printf("Impossible d'ouvrir la connexion. Veuillez lancer le service usbmuxd ou choisir un autre port.\n");
		exit(1);
	}
	printf("Ouverture de la connexion...OK\n");
	return res;
}

int talkitive_disconnect(int buffer)
{
	usbmuxd_disconnect(buffer);
}



int talkitive_send_pixel(int socket, uint x, uint y, uint color)
{

	char x_data[15];
	char y_data[15];
	char color_data[15];	
	sprintf(x_data,"%d", x);
	sprintf(y_data,"%d", y);
	sprintf(color_data,"%d", color);


	char data[80];
	strcpy(data, "pixel ");
	strcat(data, x_data);
	strcat(data, " ");
	strcat(data, y_data);
	strcat(data, " ");
	strcat(data, color_data);

	printf("Envoi de '%s'\n", data);

	int sent_bytes;

	int res = usbmuxd_send(socket, data, strlen(data), &sent_bytes);
	if(res != 0)
	{
		printf("Echec de l'envoi.\nErreur: %d\n", res);
		return res;
	}
	printf("Message envoyé. Longueur: %d\n", sent_bytes);
	return res;
}
