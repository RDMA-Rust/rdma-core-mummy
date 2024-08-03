#include <infiniband/verbs.h>
#include <stdio.h>

int main()
{
	int num_devices = 0;
	struct ibv_device **devices = ibv_get_device_list(&num_devices);
	if (devices == NULL) {
		perror("ibv_get_device_list failed");
		return -1;
	}
	printf("got %d devices\n", num_devices);
	for (int i = 0; i != num_devices; ++i) {
		printf("\tdevice %d: name=%s\n", i,
		       ibv_get_device_name(devices[i]));
	}
	ibv_free_device_list(devices);
	return 0;
}
