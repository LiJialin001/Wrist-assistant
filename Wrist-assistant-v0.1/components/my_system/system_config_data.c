#include "system_config_data.h"

_system_wifi_data *system_wifi_data;

_system_wifi_data* wifi_list_create(char * name,char *password,char *auto_connect)
{
	_system_wifi_data* NewNode = (_system_wifi_data*)heap_caps_malloc(sizeof(_system_wifi_data), MALLOC_CAP_SPIRAM);

	memset(NewNode,0x00,sizeof(_system_wifi_data));
	memcpy(NewNode->name,name,strlen(name));
	memcpy(NewNode->password,password,strlen(password));
	memcpy(NewNode->auto_connect,auto_connect,strlen(auto_connect));

	return NewNode;
}

//链表尾部插入一个节点
void wifi_list_add_node_back(_system_wifi_data **pphead,char * name,char *password,char *auto_connect)
{
	system_debug("链表尾部插入一个节点");
	_system_wifi_data * tail = *pphead;
	if(tail == NULL)
	{
		system_debug("创建新节点失败2");
		return;
	}


	_system_wifi_data * NewNode = wifi_list_create(name,password,auto_connect);
	if(NewNode == NULL)
	{
		system_debug("创建新节点失败");
		return;
	}

	if (*pphead == NULL)
	{
		*pphead = NewNode;
		system_debug("链表已经初始化");

	}
	else
	{
		system_debug("开始插入");

		while (tail->next != NULL)
		{
			tail=tail->next;
		}
		tail->next = NewNode;
	}
}
//链表头部插入一个节点
void wifi_list_add_node_front(_system_wifi_data **pphead,char * name,char *password,char *auto_connect)
{
	_system_wifi_data * NewNode = wifi_list_create(name,password,auto_connect);
	NewNode->next = *pphead;
	*pphead = NewNode;
}

//尾节点删除
void wifi_list_delete_node_back(_system_wifi_data **pphead)
{
	//链表为空
	if (*pphead == NULL)
	{
		return;
	}
	else if ((*pphead)->next == NULL)//只有一个节点
	{
		heap_caps_free(*pphead);
		*pphead = NULL;
	}
	else//有多个节点
	{
		_system_wifi_data *prev = NULL;
		_system_wifi_data *tail = *pphead;
		while (tail->next != NULL)
		{
			prev = tail;
			tail = tail->next;
		}
		heap_caps_free(tail);
		prev->next = NULL;
	}
}
//头节点删除
void wifi_list_delete_node_front(_system_wifi_data **pphead)
{
	if (*pphead == NULL)
	{
		return;
	}
	_system_wifi_data *next = (*pphead)->next;
	heap_caps_free(*pphead);
	*pphead = next;
}

//根据名字节点删除
void wifi_list_delete_node_name(_system_wifi_data **pphead,char * name)
{
	return NULL;
}

//查找值为x的节点并返回节点的指针
_system_wifi_data * wifi_list_find_name(_system_wifi_data *phead, char * name)
{
	_system_wifi_data *current = phead;
	while (current != NULL)
	{
		if(strstr(current->name,name))
		{
			return current;
		}
		current = current->next;
	}
	return NULL;
}

uint8_t system_get_wifi_data(void)
{
	const char *config_fime_path = "/spiffs/system/config.json";
	uint32_t file_size=0;

	file_size = system_get_file_size(config_fime_path);
    FILE* file = fopen(config_fime_path, "r");
    if (file == NULL)
	{
        system_debug("打开配置文件失败");
        return;
    }
	system_debug("打开配置文件成功");

    char *buf = (char*)heap_caps_malloc(file_size, MALLOC_CAP_SPIRAM);
	memset(buf,0x00,file_size);
    fread(buf, 1, file_size, file);

    fclose(file);
	system_debug("读出文件:%s\r\n",buf);

	cJSON *json_A = cJSON_Parse(buf);
	cJSON *j_wifi = cJSON_GetObjectItem(json_A,"wifi");

	if( NULL != j_wifi )
	{
		cJSON *j_wifi_item  = j_wifi->child;
		//while( j_wifi_item != NULL )//暂时只读取第一个wifi数据
		{
			char * name   = cJSON_GetObjectItem( j_wifi_item , "name")->valuestring ;
			char * password =  cJSON_GetObjectItem( j_wifi_item , "password")->valuestring ;
			char * aotuconnect =  cJSON_GetObjectItem( j_wifi_item , "auto connect")->valuestring ;
			system_debug("name:%s password:%s aotuconnect:%s\n",name,password,aotuconnect);
			//wifi_list_add_node_back(&system_wifi_data,name,password,aotuconnect);

			sprintf(system_data.wifi_name,name);
			sprintf(system_data.wifi_password,password);

			j_wifi_item = j_wifi_item->next;
		}
	}

	// cJSON * idle_policy_arry = c_json_parse_object(gps_upload_policy_cJSON, "idlePolicy");

	// if (idle_policy_arry != NULL) {
	// 	int idle_arry_size = cJSON_GetArraySize(idle_policy_arry);
	// 	for (int j = 0; j < idle_arry_size; j++) {
	// 		char *value = cJSON_GetArrayItem(idle_policy_arry, j);
	// 	}
	// }

	//cJSON_GetObjectItem(item, "text_day");

	cJSON_Delete(json_A);
	heap_caps_free(buf);
	return 0;
}

