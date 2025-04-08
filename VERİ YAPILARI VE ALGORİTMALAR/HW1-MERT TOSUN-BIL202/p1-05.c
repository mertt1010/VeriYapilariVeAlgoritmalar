void* larger (void* dataPtr1, void* dataPtr2,

int (*ptrToCmpFun)(void*, void*))
{
	if ((*ptrToCmpFun) (dataPtr1, dataPtr2) > 0)
		return dataPtr1;
	else
		return dataPtr2;
}
