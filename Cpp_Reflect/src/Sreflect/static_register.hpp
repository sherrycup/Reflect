#pragma once
#include"traits/field_trait.h"
#include"head/test.h"

// 静态注册器
Begin_Class(test)
functions(
	func_public(&test::output_num),
	func_public(&test::plus),
	func_private(&test::show),
	func_private(&test::what)
	)
variables(
	var_public(&test::a),
	var_private(&test::b),
	var_private(&test::c),
	var_public(&test::s)
	)
End_Class()
