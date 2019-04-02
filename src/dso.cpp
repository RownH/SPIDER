#include <dlfcn.h>
#include <dso.h>
#include "spider.h"
#include "qstring.h"



vector<Module*> modules_pre_surl;
vector<Module*> modules_post_header;
vector<Module*> modules_post_html;

//modules����д��cpp����ɶ�̬�������ﱻ����
//·��path�Ǿ���·��
//name�������ļ��е�����
Module* do_load(const char* path, const char* name);
{
	void* rv = NULL:
	void* handle = NULL:
	Module* module = NULL;
	//��̬������path+name+.so
	char *npath = strcat2(3, path, name, ".so");
	//���ؾ��handle��dlsym������ʱָ��ldl
	if((handle = dlopen(npath, RTLD_GLOBAL|RTLD_NOW)) == NULL)
	{
		SPIDER_LOG(SPIDER_LEVEL_ERROR, "Load module fail(dlopen):%s", dlerror());
	}
	//���ݾ�������Ǹ���̬�������ȫ�ֱ������ߺ�����
	//����������ģ������������һ����ģ������ͬ�ı��������汣�����Լ�������ָ�룬��ô���
	//name���ܹ�����
	if((rv = dlsym(handle, name)) == NULL)
	{
		SPIDER_LOG(SPIDER_LEVEL_ERROR, "Load module fail(dlopen):%s", dlerror());
	}
	
	module = (Module*) rv;
	module->init(module);
	return module;
}


