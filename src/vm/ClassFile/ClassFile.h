//
// Created by Admin on 2019/9/21.
//

#ifndef CCVM_CLASSFILE_H
#define CCVM_CLASSFILE_H
#define FOR_EACH(iter, var) for (decltype(var) iter = 0; iter < var; iter++)

#include "../interpreter/ByteCode.h"
enum ConstantTag {
    T_Utf8 = 1,
    T_Integer = 3,
    T_Float = 4,
    T_Long = 5,
    T_Double = 6,
    T_Class = 7,
    T_String = 8,
    T_Fieldref = 9,
    T_Methodref = 10,
    T_InterfaceMethodref = 11,
    T_NameAndType = 12,


    //JAVA 7+
    T_MethodHandle = 15,
    T_MethodType = 16,
    T_InvokeDynamic = 18
};
enum VariableInfoTag {
    ITEM_Top = 0,
    ITEM_Integer = 1,
    ITEM_Float = 2,
    ITEM_Null = 5,
    ITEM_UninitializedThis = 6,
    ITEM_Object = 7,
    ITEM_Uninitialized = 8,
    ITEM_Long = 4,
    ITEM_Double = 3
};


//class file struct
struct AttributeInfo {
    u2 attributeNameIndex;
    u4 attributeLength;
    virtual ~AttributeInfo() = default;
};

struct ConstantPoolInfo {
    virtual ~ConstantPoolInfo() = default;
};


//define constant

#define FIELDS_2(name, t, f)  \
    struct CONSTANT_##name : public ConstantPoolInfo { \
        static const u1 tag = ConstantTag::T_##name; \
        t f;                                    \
    };

#define FIELDS_3(name, t1, f1, t2, f2) \
    struct CONSTANT_##name : public ConstantPoolInfo {                 \
        static const u1 tag = ConstantTag::T_##name;                   \
        t1 f1;                                                  \
        t2 f2;                                                  \
    };

#define FIELDS_4(name, t1, f1, t2, f2, t3, f3)                                \
    struct CONSTANT_##name : public ConstantPoolInfo {                        \
        static const u1 tag = ConstantTag::T_##name;                          \
        t1 f1;                                                         \
        t2 f2;                                                         \
        t3 f3;                                                         \
    };

FIELDS_3(Integer,u4,bytes,int32_t,val);

FIELDS_3(Float,u4,bytes,float,val);

FIELDS_3(Long,u8,bytes,long,val);

FIELDS_3(Double,u8,bytes, double,val);

FIELDS_2(Class,u2,nameIndex);
FIELDS_2(String,u2,stringIndex);
FIELDS_3(Fieldref,u2,classIndex, u2,nameAndTypeIndex);

FIELDS_3(Methodref,u2,methodIndex, u2,nameAndTypeIndex);

FIELDS_3(InterfaceMethodref,u2,interfaceIndex,u2,nameAndTypeIndex);

FIELDS_3(NameAndType,u2,nameAndTypeIndex,u2,descriptionIndex);


//java 7+ for new java reflection
FIELDS_3(MethodHandle, u1, referenceKind, u2, referenceIndex);
FIELDS_2(MethodType, u2, descriptorIndex);
FIELDS_3(InvokeDynamic, u2, bootstrapMethodAttrIndex, u2,
        nameAndTypeIndex);

// It's a special structure whose a field is an array of dynamic size
// We need override destructor functions to realse these memory while the object
// was destorying  ----by kelthuzadx
struct CONSTANT_Utf8_info : public ConstantPoolInfo {
        static const u1 tag = ConstantTag::T_Utf8;
        u2 length;
        u1* bytes;
        ~CONSTANT_Utf8_info() override {delete[] bytes;}
    };

struct FieldInfo {
    u2 accessFlags;
    u2 nameIndex;
    u2 descriptorIndex;
    u2 attributeCount;
    AttributeInfo** attributes;
    ~FieldInfo() {
        FOR_EACH(i, attributeCount) { delete attributes[i]; }
        if (attributeCount > 0) {
            delete[] attributes;
        }
    }
};

struct MethodInfo {
    u2 accessFlags;
    u2 nameIndex;
    u2 descriptorIndex;
    u2 attributeCount;
    AttributeInfo** attributes;

    ~MethodInfo() {
        FOR_EACH(i, attributeCount) { delete attributes[i]; }
        delete[] attributes;
    }
};

struct ClassFile{
    u4 magic;
    u2 minorVersion;
    u2 majorVersion;
    u2 constPoolCount;
    ConstantPoolInfo** constantPoolInfo;
    u2 accessFlags;
    u2 thisClass;
    u2 superClass;
    u2 interfacesCount;
    u2* interfaces;
    u2 fieldsCount;
    FieldInfo* fields;
    u2 methodsCount;
    MethodInfo* methods;
    u2 attributesCount;
    AttributeInfo** attributes;
    ~ClassFile() {
        FOR_EACH(i, constPoolCount) { delete constantPoolInfo[i]; }
        delete[] constantPoolInfo;

        if (interfacesCount > 0) {
            delete[] interfaces;
        }

        if (fieldsCount > 0) {
            delete[] fields;
        }

        if (methodsCount > 0) {
            delete[] methods;
        }
        FOR_EACH(i, attributesCount) { delete attributes[i]; }
        delete[] attributes;
    }

};

#define IS_ATTR_ConstantValue(PTR) if (strcmp(PTR, "ConstantValue") == 0)
#define IS_ATTR_Code(PTR) if (strcmp(PTR, "Code") == 0)
#define IS_ATTR_StackMapTable(PTR) if (strcmp(PTR, "StackMapTable") == 0)
#define IS_ATTR_Exceptions(PTR) if (strcmp(PTR, "Exceptions") == 0)
#define IS_ATTR_BootstrapMethods(PTR) if (strcmp(PTR, "BootstrapMethods") == 0)
#define IS_ATTR_InnerClasses(PTR) if (strcmp(PTR, "InnerClasses") == 0)
#define IS_ATTR_EnclosingMethod(PTR) if (strcmp(PTR, "EnclosingMethod") == 0)
#define IS_ATTR_Synthetic(PTR) if (strcmp(PTR, "Synthetic") == 0)
#define IS_ATTR_Signature(PTR) if (strcmp(PTR, "Signature") == 0)
#define IS_ATTR_RuntimeVisibleAnnotations(PTR) \
    if (strcmp(PTR, "RuntimeVisibleAnnotations") == 0)
#define IS_ATTR_RuntimeInvisibleAnnotations(PTR) \
    if (strcmp(PTR, "RuntimeInvisibleAnnotations") == 0)
#define IS_ATTR_RuntimeVisibleParameterAnnotations(PTR) \
    if (strcmp(PTR, "RuntimeVisibleParameterAnnotations") == 0)
#define IS_ATTR_RuntimeInvisibleParameterAnnotations(PTR) \
    if (strcmp(PTR, "RuntimeInvisibleParameterAnnotations") == 0)
#define IS_ATTR_RuntimeVisibleTypeAnnotations(PTR) \
    if (strcmp(PTR, "RuntimeVisibleTypeAnnotations") == 0)
#define IS_ATTR_RuntimeInvisibleTypeAnnotations(PTR) \
    if (strcmp(PTR, "RuntimeInvisibleTypeAnnotations") == 0)
#define IS_ATTR_AnnotationDefault(PTR) \
    if (strcmp(PTR, "AnnotationDefault") == 0)
#define IS_ATTR_MethodParameters(PTR) if (strcmp(PTR, "MethodParameters") == 0)
#define IS_ATTR_SourceFile(PTR) if (strcmp(PTR, "SourceFile") == 0)
#define IS_ATTR_SourceDebugExtension(PTR) \
    if (strcmp(PTR, "SourceDebugExtension") == 0)
#define IS_ATTR_LineNumberTable(PTR) if (strcmp(PTR, "LineNumberTable") == 0)
#define IS_ATTR_LocalVariableTable(PTR) \
    if (strcmp(PTR, "LocalVariableTable") == 0)
#define IS_ATTR_LocalVariableTypeTable(PTR) \
    if (strcmp(PTR, "LocalVariableTypeTable") == 0)
#define IS_ATTR_Deprecated(PTR) if (strcmp(PTR, "Deprecated") == 0)

#define IS_STACKFRAME_same_frame(num) ((num) >= 0 && (num) <= 63)
#define IS_STACKFRAME_same_locals_1_stack_item_frame(num) \
    ((num) >= 64 && (num) <= 127)
#define IS_STACKFRAME_same_locals_1_stack_item_frame_extended(num) \
    ((num) == 247)
#define IS_STACKFRAME_chop_frame(num) ((num) >= 248 && (num) <= 250)
#define IS_STACKFRAME_same_frame_extended(num) ((num) == 251)
#define IS_STACKFRAME_append_frame(num) ((num) >= 252 && (num) <= 254)
#define IS_STACKFRAME_full_frame(num) ((num) == 255)

#define DEF_ATTRS(name) struct ATTR_##name : public AttributeInfo

struct Exceptions{
    u2 startPC;
    u2 endPC;
    u2 handlerPC;
    u2 catchType;
};

DEF_ATTRS(ConstantValue) { u2 constantValueIndex; };

struct VerificationTypeInfo {
    virtual ~VerificationTypeInfo() = default;
};

#define DEF_VTI_1(name)                                   \
struct VariableInfo_##name : public VerificationTypeInfo{\
          static const u1 tag =  VariableInfoTag::ITEM_##name;  \
                                                                \
     };

#define DEF_VTI_2(name,type,filed)                                  \
struct VariableInfo_##name : public VerificationTypeInfo{\
          static const u1 tag =  VariableInfoTag::ITEM_##name;  \
          type filed;                                                      \
     };

DEF_VTI_1(Top);
DEF_VTI_1(Integer);
DEF_VTI_1(Float);
DEF_VTI_1(Null);
DEF_VTI_1(UninitializedThis);
DEF_VTI_1(Long);
DEF_VTI_1(Double);
DEF_VTI_2(Object,u2,cpIndex);
DEF_VTI_2(Uninitialized,u2,offset);

struct stack_map_frame{
    virtual ~stack_map_frame() = default;
};
struct stack_map_frame_same_frame : public stack_map_frame{
    u1 frame_type;
};
struct same_locals_1_stack_item_frame : public stack_map_frame{
    u1 frame_type;
    VerificationTypeInfo** stack;
    ~same_locals_1_stack_item_frame() override {delete stack[0];delete[] stack;}
};
struct same_locals_1_stack_item_extended : public stack_map_frame{
    u1 frame_type;
    u2 offset_delta;
    VerificationTypeInfo** stack;
    ~same_locals_1_stack_item_extended() override {delete stack[0];delete[] stack;}
};
struct chop_frame : public stack_map_frame{
    u1 frame_type;
    u2 offset_delta;

};
struct same_frame_extended : public stack_map_frame{
    u1 frame_type;
    u2 offset_delta;

};
struct append_frame : public stack_map_frame{
    u1 frame_type;
    u2 offset_delta;
    VerificationTypeInfo** locals;
    ~append_frame() override {
        FOR_EACH(i, frame_type - 251) { delete locals[i]; }
        delete[] locals;
    }
};
struct full_frame : public stack_map_frame{
    u1 frame_type;
    u2 offset_delta;
    u2 number_of_locals;

    VerificationTypeInfo** locals;
    u2 number_of_stacks;
    VerificationTypeInfo** stack;
    ~full_frame() override {
        delete[] locals[0];delete[] locals;
        delete[] stack[0];delete[] stack;
    }
};




DEF_ATTRS(StackMapTable){
    u2 attr_name_index;
    u4 attr_length;
    u2 num_of_entries;
    stack_map_frame**  entries;
};
DEF_ATTRS(Code) {
    u2 maxStack;
    u2 maxLocals;
    u4 codeLen;
    u1* code;
    u2 exceptionTableLength;

    Exceptions * exceptionTable;

    u2 attributeCount;
    AttributeInfo** attributes;

    ~ATTR_Code() override {
        delete[] code;
        delete[] exceptionTable;
        FOR_EACH(i, attributeCount) { delete attributes[i]; }
        delete attributes;
    }
};
DEF_ATTRS(Exception){
    u2 num_of_exceptions;
    u2* exception_index_table;
    ~ATTR_Exception() override { delete[] exception_index_table; }
};
DEF_ATTRS(InnerClasses) {
        u2 numberOfClasses;

        struct _classes {
            u2 innerClassInfoIndex;
            u2 outerClassInfoIndex;
            u2 innerNameIndex;
            u2 innerClassAccessFlags;
        } * classes;
        ~ATTR_InnerClasses() override { delete[] classes; }
};
DEF_ATTRS(EnclosingMethod) {
        u2 classIndex;
        u2 methodIndex;
};
DEF_ATTRS(Synthetic){};
DEF_ATTRS(Signature){
    u2 signatureIndex;
};
DEF_ATTRS(SourceFile){
    u2 sourceFileIndex;
};
DEF_ATTRS(SourceDebugExtension){
    u1* debugExtension;

    ~ATTR_SourceDebugExtension() override {delete[] debugExtension;}
};
DEF_ATTRS(LocalVariableTable) {
        u2 localVariableTableLength;
        struct _localVariableTable {
            u2 startPC;
            u2 length;
            u2 nameIndex;
            u2 descriptorIndex;
            u2 index;
        } * localVariableTable;
        ~ATTR_LocalVariableTable() override { delete[] localVariableTable; }
};
DEF_ATTRS(LineNumberTable) {
        u2 lineNumberTableLength;

        struct _lineNumberTable {
            u2 startPC;
            u2 lineNumber;
        } * lineNumberTable;

        ~ATTR_LineNumberTable() override { delete[] lineNumberTable; }
};
DEF_ATTRS(LocalVariableTypeTable) {
        u2 localVariableTypeTableLength;

        struct _localVariableTypeTable {
            u2 startPC;
            u2 length;
            u2 nameIndex;
            u2 signatureIndex;
            u2 index;
        } * localVariableTypeTable;

        ~ATTR_LocalVariableTypeTable() override { delete[] localVariableTypeTable; }
};
DEF_ATTRS(Deprecated){};
struct ElementValue {
    u1 tag;
    virtual ~ElementValue() = default;
};

struct Annotation {
    u2 typeIndex;
    u2 numElementValuePairs;

    struct _elementValuePairs {
        u2 elementNameIndex;
        ElementValue* value;

        ~_elementValuePairs() { delete value; }
    } * elementValuePairs;

    ~Annotation() { delete[] elementValuePairs; }
};

struct ElementValue_ConstantValueIndex : public ElementValue {
    u2 constValueIndex;
};

struct ElementValue_EnumConstValue : public ElementValue {
    u2 typeNameIndex;
    u2 constNameIndex;
};

struct ElementValue_ClassInfoIndex : public ElementValue {
    u2 classInfoIndex;
};

struct ElementValue_ArrayValue : public ElementValue {
    u2 numValues;
    ElementValue** values;

    ~ElementValue_ArrayValue() override {
        FOR_EACH(i, numValues) { delete values[i]; }
        delete[] values;
    }
};

struct ElementValue_Annotation : public ElementValue {
    Annotation annotationValue;
};
DEF_ATTRS(RuntimeVisibleAnnotations) {
        u2 numAnnotations;
        Annotation* annotations;

        ~ATTR_RuntimeVisibleAnnotations() override { delete[] annotations; }
};

DEF_ATTRS(RuntimeInvisibleAnnotations) {
        u2 numAnnotations;
        Annotation* annotations;

        ~ATTR_RuntimeInvisibleAnnotations() override { delete[] annotations; }
};

DEF_ATTRS(RuntimeVisibleParameterAnnotations) {
        u1 numParameters;

        struct _parameterAnnotations {
            u2 numAnnotations;
            Annotation* annotations;

            ~_parameterAnnotations() { delete[] annotations; }
        } * parameterAnnotations;

        ~ATTR_RuntimeVisibleParameterAnnotations() override {
            delete[] parameterAnnotations;
        }
};

DEF_ATTRS(RuntimeInvisibleParameterAnnotations) {
        u1 numParameters;

        struct _parameterAnnotations {
            u2 numAnnotations;
            Annotation* annotations;

            ~_parameterAnnotations() { delete[] annotations; }
        } * parameterAnnotations;

        ~ATTR_RuntimeInvisibleParameterAnnotations() override {
            delete[] parameterAnnotations;
        }
};
struct TargetInfo {
    virtual ~TargetInfo() = default;
};

#define DEF_TARGET_WITH_1_FIELDS(name, type, field) \
    struct Target_##name : public TargetInfo {      \
        type field;                                 \
    };
#define DEF_TARGET_WITH_2_FIELDS(name, type, field, type1, field1) \
    struct Target_##name : public TargetInfo {                     \
        type field;                                                \
        type1 field1;                                              \
    };

DEF_TARGET_WITH_1_FIELDS(TypeParameter, u1, typeParameterIndex);

DEF_TARGET_WITH_1_FIELDS(SuperType, u2, superTypeIndex);

DEF_TARGET_WITH_2_FIELDS(TypeParameterBound, u1, typeParameterIndex, u1,
                         boundIndex);

struct Target_Empty : public TargetInfo {};

DEF_TARGET_WITH_1_FIELDS(FormalParameter, u1, formalParameter);

DEF_TARGET_WITH_1_FIELDS(Throws, u2, throwsTypeIndex);

struct Target_LocalVar : public TargetInfo {
    u2 tableLength;

    struct _table {
        u2 startPc;
        u2 length;
        u2 index;
    } * table;

    ~Target_LocalVar() override { delete[] table; }
};

DEF_TARGET_WITH_1_FIELDS(Catch, u2, exceptionTableIndex);

DEF_TARGET_WITH_1_FIELDS(Offset, u2, offset);

DEF_TARGET_WITH_2_FIELDS(TypeArgument, u2, offset, u1, typeArgumentIndex);

struct TypeAnnotation {
    u1 targetType;
    TargetInfo* targetInfo;

    struct TypePath {
        u1 pathLength;

        struct _path {
            u1 typePathKind;
            u1 typeArgumentIndex;
        } * path;

        ~TypePath() { delete[] path; }
    } targetPath;

    u2 typeIndex;
    u2 numElementValuePairs;

    struct _elementValuePairs {
        u2 elementNameIndex;
        ElementValue* value;

        ~_elementValuePairs() { delete value; }
    } * elementValuePairs;

    ~TypeAnnotation() {
        delete targetInfo;
        delete[] elementValuePairs;
    }
};

DEF_ATTRS(RuntimeVisibleTypeAnnotations) {
        u2 numAnnotations;
        TypeAnnotation* annotations;

        ~ATTR_RuntimeVisibleTypeAnnotations() override { delete[] annotations; }
};

DEF_ATTRS(RuntimeInvisibleTypeAnnotations) {
        u2 numAnnotations;
        TypeAnnotation* annotations;

        ~ATTR_RuntimeInvisibleTypeAnnotations() override { delete[] annotations; }
};

DEF_ATTRS(AnnotationDefault) {
        ElementValue* defaultValue;

        ~ATTR_AnnotationDefault() { delete defaultValue; }
};

DEF_ATTRS(BootstrapMethods) {
        u2 numBootstrapMethods;

        struct _bootstrapMethod {
            u2 bootstrapMethodRef;
            u2 numBootstrapArgument;
            u2* bootstrapArguments;

            ~_bootstrapMethod() { delete[] bootstrapArguments; }
        } * bootstrapMethod;

        ~ATTR_BootstrapMethods() override { delete[] bootstrapMethod; }
};

DEF_ATTRS(MethodParameter) {
        u1 parameterCount;

        struct _parameters {
            u2 nameIndex;
            u2 accessFlags;
        } * parameters;

        ~ATTR_MethodParameter() override { delete[] parameters; }
};


#endif //CCVM_CLASSFILE_H
