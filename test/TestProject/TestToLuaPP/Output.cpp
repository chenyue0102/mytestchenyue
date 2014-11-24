/*
** Lua binding: 
** Generated automatically by tolua++-1.0.92 on 06/12/14 15:52:17.
*/
#include "StdAfx.h"
#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua__open (lua_State* tolua_S);

#include "vector"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_TestTLV (lua_State* tolua_S)
{
 TestTLV* self = (TestTLV*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CMyVector_TestTLV_ (lua_State* tolua_S)
{
 CMyVector<TestTLV>* self = (CMyVector<TestTLV>*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CMyVector_TestTLV___iterator (lua_State* tolua_S)
{
 CMyVector<TestTLV>::iterator* self = (CMyVector<TestTLV>::iterator*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"TestTLV");
 tolua_usertype(tolua_S,"CMyVector<TestTLV>");
 tolua_usertype(tolua_S,"std::vector<TestTLV>");
 tolua_usertype(tolua_S,"CMyVector<TestTLV>::const_iterator");
 tolua_usertype(tolua_S,"CMyVector<TestTLV>::iterator");
}

/* get function: dwID of class  TestTLV */
#ifndef TOLUA_DISABLE_tolua_get_TestTLV_unsigned_dwID
static int tolua_get_TestTLV_unsigned_dwID(lua_State* tolua_S)
{
  TestTLV* self = (TestTLV*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwID'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->dwID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: dwID of class  TestTLV */
#ifndef TOLUA_DISABLE_tolua_set_TestTLV_unsigned_dwID
static int tolua_set_TestTLV_unsigned_dwID(lua_State* tolua_S)
{
  TestTLV* self = (TestTLV*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwID'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->dwID = ((unsigned long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: dwType of class  TestTLV */
#ifndef TOLUA_DISABLE_tolua_get_TestTLV_unsigned_dwType
static int tolua_get_TestTLV_unsigned_dwType(lua_State* tolua_S)
{
  TestTLV* self = (TestTLV*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwType'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->dwType);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: dwType of class  TestTLV */
#ifndef TOLUA_DISABLE_tolua_set_TestTLV_unsigned_dwType
static int tolua_set_TestTLV_unsigned_dwType(lua_State* tolua_S)
{
  TestTLV* self = (TestTLV*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwType'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->dwType = ((unsigned long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: strValue of class  TestTLV */
#ifndef TOLUA_DISABLE_tolua_get_TestTLV_strValue
static int tolua_get_TestTLV_strValue(lua_State* tolua_S)
{
  TestTLV* self = (TestTLV*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'strValue'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->strValue);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: strValue of class  TestTLV */
#ifndef TOLUA_DISABLE_tolua_set_TestTLV_strValue
static int tolua_set_TestTLV_strValue(lua_State* tolua_S)
{
  TestTLV* self = (TestTLV*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'strValue'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->strValue = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  TestTLV */
#ifndef TOLUA_DISABLE_tolua__TestTLV_new00
static int tolua__TestTLV_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"TestTLV",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const TestTLV",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const TestTLV* other = ((const TestTLV*)  tolua_tousertype(tolua_S,2,0));
  {
   TestTLV* tolua_ret = (TestTLV*)  Mtolua_new((TestTLV)(*other));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TestTLV");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  TestTLV */
#ifndef TOLUA_DISABLE_tolua__TestTLV_new00_local
static int tolua__TestTLV_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"TestTLV",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const TestTLV",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const TestTLV* other = ((const TestTLV*)  tolua_tousertype(tolua_S,2,0));
  {
   TestTLV* tolua_ret = (TestTLV*)  Mtolua_new((TestTLV)(*other));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TestTLV");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  TestTLV */
#ifndef TOLUA_DISABLE_tolua__TestTLV_new01
static int tolua__TestTLV_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"TestTLV",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  {
   TestTLV* tolua_ret = (TestTLV*)  Mtolua_new((TestTLV)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TestTLV");
  }
 }
 return 1;
tolua_lerror:
 return tolua__TestTLV_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  TestTLV */
#ifndef TOLUA_DISABLE_tolua__TestTLV_new01_local
static int tolua__TestTLV_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"TestTLV",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  {
   TestTLV* tolua_ret = (TestTLV*)  Mtolua_new((TestTLV)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TestTLV");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua__TestTLV_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  TestTLV */
#ifndef TOLUA_DISABLE_tolua__TestTLV_delete00
static int tolua__TestTLV_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TestTLV",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TestTLV* self = (TestTLV*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: TestTLV::SetDword of class  TestTLV */
#ifndef TOLUA_DISABLE_tolua__TestTLV_TestTLV__SetDword00
static int tolua__TestTLV_TestTLV__SetDword00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TestTLV",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TestTLV* self = (TestTLV*)  tolua_tousertype(tolua_S,1,0);
  unsigned long dwPropertyID = ((unsigned long)  tolua_tonumber(tolua_S,2,0));
  unsigned long dwPropertyValue = ((unsigned long)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'TestTLV::SetDword'", NULL);
#endif
  {
   self->TestTLV::SetDword(dwPropertyID,dwPropertyValue);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'TestTLV__SetDword'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: TestTLV::SetString of class  TestTLV */
#ifndef TOLUA_DISABLE_tolua__TestTLV_TestTLV__SetString00
static int tolua__TestTLV_TestTLV__SetString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TestTLV",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TestTLV* self = (TestTLV*)  tolua_tousertype(tolua_S,1,0);
  unsigned long dwPropertyID = ((unsigned long)  tolua_tonumber(tolua_S,2,0));
  const std::string PropertyValue = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'TestTLV::SetString'", NULL);
#endif
  {
   self->TestTLV::SetString(dwPropertyID,PropertyValue);
   tolua_pushcppstring(tolua_S,(const char*)PropertyValue);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'TestTLV__SetString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Test of class  TestTLV */
#ifndef TOLUA_DISABLE_tolua__TestTLV_Test00
static int tolua__TestTLV_Test00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TestTLV",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TestTLV* self = (TestTLV*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Test'", NULL);
#endif
  {
   self->Test();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Test'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  TestTLV */
#ifndef TOLUA_DISABLE_tolua__TestTLV__eq00
static int tolua__TestTLV__eq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const TestTLV",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const TestTLV",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const TestTLV* self = (const TestTLV*)  tolua_tousertype(tolua_S,1,0);
  const TestTLV* other = ((const TestTLV*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator==(*other);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.eq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator* of class  TestTLV */
#ifndef TOLUA_DISABLE_tolua__TestTLV__mul00
static int tolua__TestTLV__mul00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TestTLV",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TestTLV* self = (TestTLV*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator*'", NULL);
#endif
  {
   TestTLV& tolua_ret = (TestTLV&)  self->operator*();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"TestTLV");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.mul'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: g_lCount of class  TestTLV */
#ifndef TOLUA_DISABLE_tolua_get_TestTLV_g_lCount
static int tolua_get_TestTLV_g_lCount(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)TestTLV::g_lCount);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: g_lCount of class  TestTLV */
#ifndef TOLUA_DISABLE_tolua_set_TestTLV_g_lCount
static int tolua_set_TestTLV_g_lCount(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  TestTLV::g_lCount = ((long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CMyVector<TestTLV> */
#ifndef TOLUA_DISABLE_tolua__CMyVector_TestTLV__new00
static int tolua__CMyVector_TestTLV__new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMyVector<TestTLV>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CMyVector<TestTLV>* tolua_ret = (CMyVector<TestTLV>*)  Mtolua_new((CMyVector<TestTLV>)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMyVector<TestTLV>");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CMyVector<TestTLV> */
#ifndef TOLUA_DISABLE_tolua__CMyVector_TestTLV__new00_local
static int tolua__CMyVector_TestTLV__new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMyVector<TestTLV>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CMyVector<TestTLV>* tolua_ret = (CMyVector<TestTLV>*)  Mtolua_new((CMyVector<TestTLV>)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMyVector<TestTLV>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CMyVector<TestTLV> */
#ifndef TOLUA_DISABLE_tolua__CMyVector_TestTLV__delete00
static int tolua__CMyVector_TestTLV__delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMyVector<TestTLV>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMyVector<TestTLV>* self = (CMyVector<TestTLV>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Test of class  CMyVector<TestTLV> */
#ifndef TOLUA_DISABLE_tolua__CMyVector_TestTLV__Test00
static int tolua__CMyVector_TestTLV__Test00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMyVector<TestTLV>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMyVector<TestTLV>* self = (CMyVector<TestTLV>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Test'", NULL);
#endif
  {
   self->Test();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Test'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: push_back of class  CMyVector<TestTLV> */
#ifndef TOLUA_DISABLE_tolua__CMyVector_TestTLV__push_back00
static int tolua__CMyVector_TestTLV__push_back00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMyVector<TestTLV>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const TestTLV",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMyVector<TestTLV>* self = (CMyVector<TestTLV>*)  tolua_tousertype(tolua_S,1,0);
  const TestTLV* value = ((const TestTLV*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'push_back'", NULL);
#endif
  {
   self->push_back(*value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'push_back'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: erase of class  CMyVector<TestTLV> */
#ifndef TOLUA_DISABLE_tolua__CMyVector_TestTLV__erase00
static int tolua__CMyVector_TestTLV__erase00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMyVector<TestTLV>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CMyVector<TestTLV>::const_iterator",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMyVector<TestTLV>* self = (CMyVector<TestTLV>*)  tolua_tousertype(tolua_S,1,0);
  CMyVector<TestTLV>::const_iterator _Where = *((CMyVector<TestTLV>::const_iterator*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'erase'", NULL);
#endif
  {
   CMyVector<TestTLV>::iterator tolua_ret = (CMyVector<TestTLV>::iterator)  self->erase(_Where);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CMyVector<TestTLV>::iterator)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CMyVector<TestTLV>::iterator");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CMyVector<TestTLV>::iterator));
     tolua_pushusertype(tolua_S,tolua_obj,"CMyVector<TestTLV>::iterator");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'erase'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: insert of class  CMyVector<TestTLV> */
#ifndef TOLUA_DISABLE_tolua__CMyVector_TestTLV__insert00
static int tolua__CMyVector_TestTLV__insert00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMyVector<TestTLV>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CMyVector<TestTLV>::const_iterator",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const TestTLV",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMyVector<TestTLV>* self = (CMyVector<TestTLV>*)  tolua_tousertype(tolua_S,1,0);
  CMyVector<TestTLV>::const_iterator _Where = *((CMyVector<TestTLV>::const_iterator*)  tolua_tousertype(tolua_S,2,0));
  const TestTLV* _Val = ((const TestTLV*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'insert'", NULL);
#endif
  {
   CMyVector<TestTLV>::iterator tolua_ret = (CMyVector<TestTLV>::iterator)  self->insert(_Where,*_Val);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CMyVector<TestTLV>::iterator)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CMyVector<TestTLV>::iterator");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CMyVector<TestTLV>::iterator));
     tolua_pushusertype(tolua_S,tolua_obj,"CMyVector<TestTLV>::iterator");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'insert'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clear of class  CMyVector<TestTLV> */
#ifndef TOLUA_DISABLE_tolua__CMyVector_TestTLV__clear00
static int tolua__CMyVector_TestTLV__clear00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMyVector<TestTLV>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMyVector<TestTLV>* self = (CMyVector<TestTLV>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clear'", NULL);
#endif
  {
   self->clear();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clear'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: size of class  CMyVector<TestTLV> */
#ifndef TOLUA_DISABLE_tolua__CMyVector_TestTLV__size00
static int tolua__CMyVector_TestTLV__size00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CMyVector<TestTLV>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CMyVector<TestTLV>* self = (const CMyVector<TestTLV>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'size'", NULL);
#endif
  {
   int tolua_ret = (int)  self->size();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'size'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator[] of class  CMyVector<TestTLV> */
#ifndef TOLUA_DISABLE_tolua__CMyVector_TestTLV___geti00
static int tolua__CMyVector_TestTLV___geti00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CMyVector<TestTLV>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CMyVector<TestTLV>* self = (const CMyVector<TestTLV>*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator[]'", NULL);
#endif
  {
   const TestTLV tolua_ret = (const TestTLV)  self->operator[](index);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((TestTLV)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"const TestTLV");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(const TestTLV));
     tolua_pushusertype(tolua_S,tolua_obj,"const TestTLV");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.geti'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator&[] of class  CMyVector<TestTLV> */
#ifndef TOLUA_DISABLE_tolua__CMyVector_TestTLV___seti00
static int tolua__CMyVector_TestTLV___seti00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMyVector<TestTLV>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"TestTLV",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMyVector<TestTLV>* self = (CMyVector<TestTLV>*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
  TestTLV tolua_value = *((TestTLV*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator&[]'", NULL);
#endif
  self->operator[](index) =  tolua_value;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.seti'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator[] of class  CMyVector<TestTLV> */
#ifndef TOLUA_DISABLE_tolua__CMyVector_TestTLV___geti01
static int tolua__CMyVector_TestTLV___geti01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMyVector<TestTLV>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CMyVector<TestTLV>* self = (CMyVector<TestTLV>*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator[]'", NULL);
#endif
  {
   TestTLV tolua_ret = (TestTLV)  self->operator[](index);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((TestTLV)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"TestTLV");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(TestTLV));
     tolua_pushusertype(tolua_S,tolua_obj,"TestTLV");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua__CMyVector_TestTLV___geti00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: begin of class  CMyVector<TestTLV> */
#ifndef TOLUA_DISABLE_tolua__CMyVector_TestTLV__begin00
static int tolua__CMyVector_TestTLV__begin00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMyVector<TestTLV>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMyVector<TestTLV>* self = (CMyVector<TestTLV>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'begin'", NULL);
#endif
  {
   CMyVector<TestTLV>::iterator tolua_ret = (CMyVector<TestTLV>::iterator)  self->begin();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CMyVector<TestTLV>::iterator)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CMyVector<TestTLV>::iterator");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CMyVector<TestTLV>::iterator));
     tolua_pushusertype(tolua_S,tolua_obj,"CMyVector<TestTLV>::iterator");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'begin'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: end of class  CMyVector<TestTLV> */
#ifndef TOLUA_DISABLE_tolua__CMyVector_TestTLV__end00
static int tolua__CMyVector_TestTLV__end00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMyVector<TestTLV>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMyVector<TestTLV>* self = (CMyVector<TestTLV>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'end'", NULL);
#endif
  {
   CMyVector<TestTLV>::iterator tolua_ret = (CMyVector<TestTLV>::iterator)  self->end();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CMyVector<TestTLV>::iterator)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CMyVector<TestTLV>::iterator");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CMyVector<TestTLV>::iterator));
     tolua_pushusertype(tolua_S,tolua_obj,"CMyVector<TestTLV>::iterator");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'end'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua__open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"TestTLV","TestTLV","",tolua_collect_TestTLV);
  #else
  tolua_cclass(tolua_S,"TestTLV","TestTLV","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"TestTLV");
   tolua_variable(tolua_S,"dwID",tolua_get_TestTLV_unsigned_dwID,tolua_set_TestTLV_unsigned_dwID);
   tolua_variable(tolua_S,"dwType",tolua_get_TestTLV_unsigned_dwType,tolua_set_TestTLV_unsigned_dwType);
   tolua_variable(tolua_S,"strValue",tolua_get_TestTLV_strValue,tolua_set_TestTLV_strValue);
   tolua_function(tolua_S,"new",tolua__TestTLV_new00);
   tolua_function(tolua_S,"new_local",tolua__TestTLV_new00_local);
   tolua_function(tolua_S,".call",tolua__TestTLV_new00_local);
   tolua_function(tolua_S,"new",tolua__TestTLV_new01);
   tolua_function(tolua_S,"new_local",tolua__TestTLV_new01_local);
   tolua_function(tolua_S,".call",tolua__TestTLV_new01_local);
   tolua_function(tolua_S,"delete",tolua__TestTLV_delete00);
   tolua_function(tolua_S,"TestTLV__SetDword",tolua__TestTLV_TestTLV__SetDword00);
   tolua_function(tolua_S,"TestTLV__SetString",tolua__TestTLV_TestTLV__SetString00);
   tolua_function(tolua_S,"Test",tolua__TestTLV_Test00);
   tolua_function(tolua_S,".eq",tolua__TestTLV__eq00);
   tolua_function(tolua_S,".mul",tolua__TestTLV__mul00);
   tolua_variable(tolua_S,"g_lCount",tolua_get_TestTLV_g_lCount,tolua_set_TestTLV_g_lCount);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CMyVector_TestTLV_","CMyVector<TestTLV>","std::vector<TestTLV>",tolua_collect_CMyVector_TestTLV_);
  #else
  tolua_cclass(tolua_S,"CMyVector_TestTLV_","CMyVector<TestTLV>","std::vector<TestTLV>",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CMyVector_TestTLV_");
   tolua_function(tolua_S,"new",tolua__CMyVector_TestTLV__new00);
   tolua_function(tolua_S,"new_local",tolua__CMyVector_TestTLV__new00_local);
   tolua_function(tolua_S,".call",tolua__CMyVector_TestTLV__new00_local);
   tolua_function(tolua_S,"delete",tolua__CMyVector_TestTLV__delete00);
   tolua_function(tolua_S,"Test",tolua__CMyVector_TestTLV__Test00);
   tolua_function(tolua_S,"push_back",tolua__CMyVector_TestTLV__push_back00);
   tolua_function(tolua_S,"erase",tolua__CMyVector_TestTLV__erase00);
   tolua_function(tolua_S,"insert",tolua__CMyVector_TestTLV__insert00);
   tolua_function(tolua_S,"clear",tolua__CMyVector_TestTLV__clear00);
   tolua_function(tolua_S,"size",tolua__CMyVector_TestTLV__size00);
   tolua_function(tolua_S,".geti",tolua__CMyVector_TestTLV___geti00);
   tolua_function(tolua_S,".seti",tolua__CMyVector_TestTLV___seti00);
   tolua_function(tolua_S,".geti",tolua__CMyVector_TestTLV___geti01);
   tolua_function(tolua_S,"begin",tolua__CMyVector_TestTLV__begin00);
   tolua_function(tolua_S,"end",tolua__CMyVector_TestTLV__end00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_ (lua_State* tolua_S) {
 return tolua__open(tolua_S);
};
#endif

