#pragma once

#pragma region FOR_EACH

#define PARENS ()
#define NEXT_ELEM ,

#define RESCAN(...) RESCAN1(RESCAN1(RESCAN1(RESCAN1(__VA_ARGS__))))
#define RESCAN1(...) RESCAN2(RESCAN2(RESCAN2(RESCAN2(__VA_ARGS__))))
#define RESCAN2(...) RESCAN3(RESCAN3(RESCAN3(RESCAN3(__VA_ARGS__))))
#define RESCAN3(...) RESCAN4(RESCAN4(RESCAN4(RESCAN4(__VA_ARGS__))))
#define RESCAN4(...) __VA_ARGS__

#pragma region SINGLE_FOR_EACH

#define DO_FOR_EACH(func, ...)\
	__VA_OPT__(RESCAN(DO_FOR_EACH_HELPER(func, __VA_ARGS__)))
#define DO_FOR_EACH_HELPER(func, a1, ...)\
	func(a1)\
	__VA_OPT__(DO_FOR_EACH_AGAIN PARENS (func, __VA_ARGS__))
#define DO_FOR_EACH_AGAIN() DO_FOR_EACH_HELPER

#define LIST_DO_FOR_EACH(func, ...)\
	__VA_OPT__(RESCAN(LIST_DO_FOR_EACH_HELPER(func, __VA_ARGS__)))
#define LIST_DO_FOR_EACH_HELPER(func, a1, ...)\
	func(a1)\
	__VA_OPT__(NEXT_ELEM LIST_DO_FOR_EACH_AGAIN PARENS (func, __VA_ARGS__))
#define LIST_DO_FOR_EACH_AGAIN() LIST_DO_FOR_EACH_HELPER

#pragma endregion

#pragma region PAIR_FOR_EACH

#define DO_FOR_EACH_PAIR(func, a1, ...)\
	__VA_OPT__(RESCAN(DO_FOR_EACH_PAIR_HELPER(func, a1, __VA_ARGS__)))
#define DO_FOR_EACH_PAIR_HELPER(func, a1, a2, ...)\
	func(a1, a2)\
	__VA_OPT__(DO_FOR_EACH_PAIR_AGAIN PARENS (func, __VA_ARGS__))
#define DO_FOR_EACH_PAIR_AGAIN() DO_FOR_EACH_PAIR_HELPER

#define LIST_DO_FOR_EACH_PAIR(func, a1, ...)\
	__VA_OPT__(RESCAN(LIST_DO_FOR_EACH_PAIR_HELPER(func, a1, __VA_ARGS__)))
#define LIST_DO_FOR_EACH_PAIR_HELPER(func, a1, a2, ...)\
	func(a1, a2)\
	__VA_OPT__(NEXT_ELEM LIST_DO_FOR_EACH_PAIR_AGAIN PARENS (func, __VA_ARGS__))
#define LIST_DO_FOR_EACH_PAIR_AGAIN() LIST_DO_FOR_EACH_PAIR_HELPER

#pragma endregion

#pragma region THREE_FOR_EACH

#define DO_FOR_EACH_THREE(func, a1, ...)\
	__VA_OPT__(RESCAN(DO_FOR_EACH_THREE_HELPER(func, a1, __VA_ARGS__)))
#define DO_FOR_EACH_THREE_HELPER(func, a1, a2, a3, ...)\
	func(a1, a2, a3)\
	__VA_OPT__(DO_FOR_EACH_THREE_AGAIN PARENS (func, __VA_ARGS__))
#define DO_FOR_EACH_THREE_AGAIN() DO_FOR_EACH_THREE_HELPER

#define LIST_DO_FOR_EACH_THREE(func, a1, ...)\
	__VA_OPT__(RESCAN(LIST_DO_FOR_EACH_THREE_HELPER(func, a1, __VA_ARGS__)))
#define LIST_DO_FOR_EACH_THREE_HELPER(func, a1, a2, a3, ...)\
	func(a1, a2, a3)\
	__VA_OPT__(NEXT_ELEM LIST_DO_FOR_EACH_THREE_AGAIN PARENS (func, __VA_ARGS__))
#define LIST_DO_FOR_EACH_THREE_AGAIN() LIST_DO_FOR_EACH_THREE_HELPER

#pragma endregion

#pragma endregion

#pragma region ENUMS

#pragma region STANDARD_ENUMS

#define ENUM_ELEMENT(name) name
#define ENUM_ELEMENT_COUNT(...) 1 +
#define ENUM_CASE(name, ...) case name: return #name;

#define ENUM(name, ...)\
	enum name { LIST_DO_FOR_EACH(ENUM_ELEMENT, __VA_ARGS__) };\
	template<class T> static size_t size();\
	template<> static size_t size<name>() {\
		return DO_FOR_EACH(ENUM_ELEMENT_COUNT, __VA_ARGS__) 0;\
	}\
	static std::string to_string(name value) {\
		using enum name;\
		switch(value) {\
		DO_FOR_EACH(ENUM_CASE, __VA_ARGS__)\
		default:\
			return "UNKONWN";\
		}\
	}

#define ENUM_BASE(name, base, ...)\
	enum name : base { LIST_DO_FOR_EACH(ENUM_ELEMENT, __VA_ARGS__) };\
	template<class T> static size_t size();\
	template<> static size_t size<name>() {\
		return DO_FOR_EACH(ENUM_ELEMENT_COUNT, __VA_ARGS__) 0;\
	}\
	static std::string to_string(name value) {\
		using enum name;\
		switch(value) {\
		DO_FOR_EACH(ENUM_CASE, __VA_ARGS__)\
		default:\
			return "UNKONWN";\
		}\
	}

#define ENUM_CLASS(name, ...)\
	enum class name { LIST_DO_FOR_EACH(ENUM_ELEMENT, __VA_ARGS__) };\
	template<class T> static size_t size();\
	template<> static size_t size<name>() {\
		return DO_FOR_EACH(ENUM_ELEMENT_COUNT, __VA_ARGS__) 0;\
	}\
	static std::string to_string(name value) {\
		using enum name;\
		switch(value) {\
		DO_FOR_EACH(ENUM_CASE, __VA_ARGS__)\
		default:\
			return "UNKNOWN";\
		}\
	}

#define ENUM_CLASS_BASE(name, base, ...)\
	enum class name : base { LIST_DO_FOR_EACH(ENUM_ELEMENT, __VA_ARGS__) };\
	template<class T> static size_t size();\
	template<> static size_t size<name>() {\
		return DO_FOR_EACH(ENUM_ELEMENT_COUNT, __VA_ARGS__) 0;\
	}\
	static std::string to_string(name value) {\
		using enum name;\
		switch(value) {\
		DO_FOR_EACH(ENUM_CASE, __VA_ARGS__)\
		default:\
			return "UNKNOWN";\
		}\
	}
#pragma endregion

#pragma region STANDARD_ENUMS_WITH_USER_DEFINED_TO_STRING

#define FIRST_ELEM(A, B, ...) A
#define SECOND_ELEM(A, B, ...) B
#define STANDARD_ENUM_STRING(name) name, #name
#define ENUM_STRING_CASE(name, value, ...) case name: return value;

#define ENUM_STRING(name, ...)\
	enum name { LIST_DO_FOR_EACH_PAIR(FIRST_ELEM, __VA_ARGS__) };\
	template<class T> static size_t size();\
	template<> static size_t size<name>() {\
		return DO_FOR_EACH_PAIR(ENUM_ELEMENT_COUNT, __VA_ARGS__) 0;\
	}\
	static std::string to_string(name value) {\
		using enum name;\
		switch(value) {\
		DO_FOR_EACH_PAIR(ENUM_STRING_CASE, __VA_ARGS__)\
		default:\
			return "UNKONWN";\
		}\
	}

#define ENUM_BASE_STRING(name, base, ...)\
	enum name : base { LIST_DO_FOR_EACH_PAIR(FIRST_ELEM, __VA_ARGS__) };\
	template<class T> static size_t size();\
	template<> static size_t size<name>() {\
		return DO_FOR_EACH_PAIR(ENUM_ELEMENT_COUNT, __VA_ARGS__) 0;\
	}\
	static std::string to_string(name value) {\
		using enum name;\
		switch(value) {\
		DO_FOR_EACH_PAIR(ENUM_STRING_CASE, __VA_ARGS__)\
		default:\
			return "UNKONWN";\
		}\
	}

#define ENUM_CLASS_STRING(name, ...)\
	enum class name { LIST_DO_FOR_EACH_PAIR(FIRST_ELEM, __VA_ARGS__) };\
	template<class T> static size_t size();\
	template<> static size_t size<name>() {\
		return DO_FOR_EACH_PAIR(ENUM_ELEMENT_COUNT, __VA_ARGS__) 0;\
	}\
	static std::string to_string(name value) {\
		using enum name;\
		switch(value) {\
		DO_FOR_EACH_PAIR(ENUM_STRING_CASE, __VA_ARGS__)\
		default:\
			return "UNKNOWN";\
		}\
	}

#define ENUM_CLASS_BASE_STRING(name, base, ...)\
	enum class name : base { LIST_DO_FOR_EACH_PAIR(FIRST_ELEM, __VA_ARGS__) };\
	template<class T> static size_t size();\
	template<> static size_t size<name>() {\
		return DO_FOR_EACH_PAIR(ENUM_ELEMENT_COUNT, __VA_ARGS__) 0;\
	}\
	static std::string to_string(name value) {\
		using enum name;\
		switch(value) {\
		DO_FOR_EACH_PAIR(ENUM_STRING_CASE, __VA_ARGS__)\
		default:\
			return "UNKNOWN";\
		}\
	}
#pragma endregion

#pragma region ENUMS_WITH_VALUES

#define ENUM_ELEMENT_VALUE(name, value) name = value

#define ENUM_VALUE(name, ...)\
	enum name { LIST_DO_FOR_EACH_PAIR(ENUM_ELEMENT_VALUE, __VA_ARGS__) };\
	template<class T> static size_t size();\
	template<> static size_t size<name>() {\
		return DO_FOR_EACH_PAIR(ENUM_ELEMENT_COUNT, __VA_ARGS__) 0;\
	}\
	static std::string to_string(name value) {\
		using enum name;\
		switch(value) {\
		DO_FOR_EACH_PAIR(ENUM_CASE, __VA_ARGS__)\
		default:\
			return "UNKONWN";\
		}\
	}

#define ENUM_BASE_VALUE(name, base, ...)\
	enum name : base { LIST_DO_FOR_EACH_PAIR(ENUM_ELEMENT_VALUE, __VA_ARGS__) };\
	template<class T> static size_t size();\
	template<> static size_t size<name>() {\
		return DO_FOR_EACH_PAIR(ENUM_ELEMENT_COUNT, __VA_ARGS__) 0;\
	}\
	static std::string to_string(name value) {\
		using enum name;\
		switch(value) {\
		DO_FOR_EACH_PAIR(ENUM_CASE, __VA_ARGS__)\
		default:\
			return "UNKONWN";\
		}\
	}

#define ENUM_CLASS_VALUE(name, ...)\
	enum class name { LIST_DO_FOR_EACH_PAIR(ENUM_ELEMENT_VALUE, __VA_ARGS__) };\
	template<class T> static size_t size();\
	template<> static size_t size<name>() {\
		return DO_FOR_EACH_PAIR(ENUM_ELEMENT_COUNT, __VA_ARGS__) 0;\
	}\
	static std::string to_string(name value) {\
		using enum name;\
		switch(value) {\
		DO_FOR_EACH_PAIR(ENUM_CASE, __VA_ARGS__)\
		default:\
			return "UNKONWN";\
		}\
	}

#define ENUM_CLASS_BASE_VALUE(name, base, ...)\
	enum class name : base { LIST_DO_FOR_EACH_PAIR(ENUM_ELEMENT_VALUE, __VA_ARGS__) };\
	template<class T> static size_t size();\
	template<> static size_t size<name>() {\
		return DO_FOR_EACH_PAIR(ENUM_ELEMENT_COUNT, __VA_ARGS__) 0;\
	}\
	static std::string to_string(name value) {\
		using enum name;\
		switch(value) {\
		DO_FOR_EACH_PAIR(ENUM_CASE, __VA_ARGS__)\
		default:\
			return "UNKONWN";\
		}\
	}

#pragma endregion

#pragma region ENUMS_WITH_VALUES_WITH_USER_DEFINED_TO_STRING

#define ENUM_ELEMENT_VALUE_STRING(name, stringVal, value) name = value

#define ENUM_STRING_VALUE(name, ...)\
	enum name { LIST_DO_FOR_EACH_THREE(ENUM_ELEMENT_VALUE_STRING, __VA_ARGS__) };\
	template<class T> static size_t size();\
	template<> static size_t size<name>() {\
		return DO_FOR_EACH_THREE(ENUM_ELEMENT_COUNT, __VA_ARGS__) 0;\
	}\
	static std::string to_string(name value) {\
		using enum name;\
		switch(value) {\
		DO_FOR_EACH_THREE(ENUM_STRING_CASE, __VA_ARGS__)\
		default:\
			return "UNKONWN";\
		}\
	}

#define ENUM_BASE_STRING_VALUE(name, base, ...)\
	enum name : base { LIST_DO_FOR_EACH_THREE(ENUM_ELEMENT_VALUE_STRING, __VA_ARGS__) };\
	template<class T> static size_t size();\
	template<> static size_t size<name>() {\
		return DO_FOR_EACH_THREE(ENUM_ELEMENT_COUNT, __VA_ARGS__) 0;\
	}\
	static std::string to_string(name value) {\
		using enum name;\
		switch(value) {\
		DO_FOR_EACH_THREE(ENUM_STRING_CASE, __VA_ARGS__)\
		default:\
			return "UNKONWN";\
		}\
	}

#define ENUM_CLASS_STRING_VALUE(name, ...)\
	enum class name { LIST_DO_FOR_EACH_THREE(ENUM_ELEMENT_VALUE_STRING, __VA_ARGS__) };\
	template<class T> static size_t size();\
	template<> static size_t size<name>() {\
		return DO_FOR_EACH_THREE(ENUM_ELEMENT_COUNT, __VA_ARGS__) 0;\
	}\
	static std::string to_string(name value) {\
		using enum name;\
		switch(value) {\
		DO_FOR_EACH_THREE(ENUM_STRING_CASE, __VA_ARGS__)\
		default:\
			return "UNKONWN";\
		}\
	}

#define ENUM_CLASS_BASE_STRING_VALUE(name, base, ...)\
	enum class name : base { LIST_DO_FOR_EACH_THREE(ENUM_ELEMENT_VALUE_STRING, __VA_ARGS__) };\
	template<class T> static size_t size();\
	template<> static size_t size<name>() {\
		return DO_FOR_EACH_THREE(ENUM_ELEMENT_COUNT, __VA_ARGS__) 0;\
	}\
	static std::string to_string(name value) {\
		using enum name;\
		switch(value) {\
		DO_FOR_EACH_THREE(ENUM_STRING_CASE, __VA_ARGS__)\
		default:\
			return "UNKONWN";\
		}\
	}

#pragma endregion

#pragma endregion

#pragma region CLONE_FUNC

#define CloneFuncAbstractDeclaration(className)\
	virtual className* Clone() const = 0;

#define CloneFuncDeclaration(className)\
    virtual className* Clone() const;\
    void CloneTo(className* cloned) const;

#define CloneBaseFuncDeclaration(className)\
    virtual className* Clone() const override;\
    void CloneTo(className* cloned) const;

#define StandardClone(fieldName) fieldName, fieldName
#define PointerDeepClone(fieldName, valueType) fieldName, new valueType(*fieldName)
#define CloneFieldPair(fieldName, value) cloned->fieldName = value;

#define CloneFuncInClassDefinition(className, ...)\
    virtual className* Clone() const\
    {\
        className* cloned = new className();\
        CloneTo(cloned);\
        return cloned;\
    }\
    void CloneTo(className* cloned) const\
    {\
        DO_FOR_EACH_PAIR(CloneFieldPair, __VA_ARGS__)\
    }

#define CloneBaseFuncInClassDefinition(className, baseClassName, ...)\
    virtual className* Clone() const override\
    {\
        className* cloned = new className();\
        CloneTo(cloned);\
        return cloned;\
    }\
    void CloneTo(className* cloned) const\
    {\
        baseClassName::CloneTo(cloned);\
        DO_FOR_EACH_PAIR(CloneFieldPair, __VA_ARGS__)\
    }

#define CloneFuncDefinition(className, ...)\
    className* className::Clone() const\
    {\
        className* cloned = new className();\
        CloneTo(cloned);\
        return cloned;\
    }\
    void className::CloneTo(className* cloned) const\
    {\
        DO_FOR_EACH_PAIR(CloneFieldPair, __VA_ARGS__)\
    }

#define CloneBaseFuncDefinition(className, baseClassName, ...)\
    className* className::Clone() const\
    {\
        className* cloned = new className();\
        CloneTo(cloned);\
        return cloned;\
    }\
    void className::CloneTo(className* cloned) const\
    {\
        baseClassName::CloneTo(cloned);\
        DO_FOR_EACH_PAIR(CloneFieldPair, __VA_ARGS__)\
    }


#define CloneAdvancedBaseFunc(className, baseClassName, ...) CloneBaseFuncInClassDefinition(className, baseClassName, __VA_ARGS__)
#define CloneAdvancedFunc(className, baseClassName, ...) CloneFuncInClassDefinition(className, baseClassName, __VA_ARGS__)
#define CloneFunc(className, ...) CloneAdvancedFunc(className, LIST_DO_FOR_EACH(StandardClone, __VA_ARGS__))
#define CloneBaseFunc(className, baseClassName, ...) CloneAdvancedBaseFunc(className, baseClassName, LIST_DO_FOR_EACH(StandardClone, __VA_ARGS__))

#define DeclareAbstractCloneFunc(className) CloneFuncAbstractDeclaration(className)
#define DeclareCloneFunc(className) CloneFuncDeclaration(className)
#define DeclareCloneBaseFunc(className) CloneBaseFuncDeclaration(className)

#define DefineCloneFunc(className, ...) CloneFuncDefinition(className, __VA_ARGS__)
#define DefineCloneBaseFunc(className, baseClassName, ...) CloneBaseFuncDefinition(className, baseClassName, __VA_ARGS__)

#pragma endregion

#pragma region OTHER

#define VAR_TO_STRING(var) #var

#pragma endregion