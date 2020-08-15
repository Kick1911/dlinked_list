APP_NAME = dlinked_list
VERSION = 0.0.1
DEPENDENCIES = 
INSTALL_PATH = /opt
CFLAGS += 

STATIC_DEP = ${shell echo ${DEPENDENCIES} | awk -v RS=' ' 'match($$0, "lib(.+).a.[0-9].[0-9].[0-9]", a) {print a[1]}'}
SHARED_DEP = ${shell echo ${DEPENDENCIES} | awk -v RS=' ' 'match($$0, "lib(.+).so.[0-9].[0-9].[0-9]", a) {print a[1]}'}
LDFLAGS += ${STATIC_DEP:%=-l%} ${SHARED_DEP:%=-l%}
