//
// Created by ChiCex on 2019/9/20.
// Mostly copy from YVM's JavaClass.h
//
#include "JavaClass.h"
#include <iostream>
#include <new>
#include <typeinfo>
#include <cstring>

JavaClass::JavaClass(const string &filepath) : reader(filepath) {
     file.attributes = nullptr;
     file.constantPoolInfo = nullptr;
     file.fields= nullptr;
     file.interfaces=nullptr;
}
JavaClass::~JavaClass() {
    for (auto& i : staticVars) {
        delete i.second;
    }
}
JavaClass::JavaClass(const JavaClass &rhs) {
     file = rhs.file;
}
void JavaClass::parseClassFile() {
    file.magic = reader.readU4();
    if(file.magic != 0xCAFEBABE){
        std::cout<<"Not a java class file,stopped"<<endl;
    }else{
        file.majorVersion = reader.readU2();
        file.minorVersion = reader.readU2();
    }
    file.constPoolCount=reader.readU2();

    if(file.constPoolCount>0)
    {parseConstantPool(file.constPoolCount);}

    file.accessFlags = reader.readU2();
    file.thisClass = reader.readU2();
    file.superClass = reader.readU2();

    file.interfacesCount = reader.readU2();
    parseInterface(file.interfacesCount);

    file.fieldsCount = reader.readU2();
    if(file.fieldsCount > 0){
        parseFields(file.fieldsCount);
    }
    file.methodsCount = reader.readU2();
    if(file.methodsCount > 0){
        parseMethod(file.methodsCount);
    }
    file.attributesCount =reader.readU2();
    if(file.attributesCount > 0){
        parseAttribute(file.attributes,file.attributesCount);
    }
    if (!reader.haveNoExtraBytes()) {
        cerr << __func__ << ":Extra bytes existed in class file\n";
    }
    return;

    error:
    cerr<<"parseClassFileErorr"<<endl;
}

void JavaClass::showJavaClassMsg() {
    cout<<"magic: "<<hex<<file.magic<<endl;
    cout<<"majorV: "<<hex<<file.majorVersion<<endl;
    cout<<"minorV: "<<hex<<file.minorVersion<<endl;
    cout<<"constPoolCount: "<<dec<<file.constPoolCount<<endl;
    cout<<"fieldsCount: "<<dec<<file.fieldsCount<<endl;
    for(int i=0;i<file.fieldsCount;i++){
    cout<<"fieldsName: "<< dynamic_cast<CONSTANT_Utf8_info*>(file.constantPoolInfo[file.fields[i].descriptorIndex])->bytes<<endl;
    }
    cout<<"methodCount: "<<dec<<file.methodsCount<<endl;
    for(int i = 0;i<(int)file.methodsCount;i++){
    cout<<"methodsName: "<<dynamic_cast<CONSTANT_Utf8_info*>(file.constantPoolInfo[file.methods[i].nameIndex])->bytes << endl;
    cout<<"method attrCount: "<<dec<<file.methods->attributeCount<<endl;
       for(int a = 0;a<file.methods[i].attributeCount;a++){
           cout<<"method attrName: "<<dec<<dynamic_cast<CONSTANT_Utf8_info*>(file.constantPoolInfo[(file.methods->attributes)[a]->attributeNameIndex])->bytes<<endl;
       }
    }

    cout<<"attrsCount: "<<dec<<file.attributesCount<<endl;
    for(int i = 0;i<file.attributesCount;i++){
    cout<<"attrsName: "<<dynamic_cast<CONSTANT_Utf8_info*>(file.constantPoolInfo[(file.attributes[i])->attributeNameIndex])->bytes<<endl;
    }
}

void JavaClass::parseConstantPool(u2 cp_count) {
    file.constantPoolInfo = new ConstantPoolInfo*[cp_count];
    file.constantPoolInfo[0] = nullptr;
    u1 tag;
    for(int i=1;i<=cp_count-1;i++){
        tag = reader.readU1();
        ConstantPoolInfo* slot;
        switch(tag){
            case T_Class:{
                 slot = new CONSTANT_Class();
                dynamic_cast<CONSTANT_Class*>(slot)->nameIndex =reader.readU2();
                file.constantPoolInfo[i] = dynamic_cast<CONSTANT_Class*>(slot);
                break;
            }
            case T_Integer:{
                slot = new CONSTANT_Integer();
                dynamic_cast<CONSTANT_Integer*>(slot)->bytes =reader.readU4();
                dynamic_cast<CONSTANT_Integer*>(slot)->val = dynamic_cast<CONSTANT_Integer*>(slot)->bytes;
                file.constantPoolInfo[i] = dynamic_cast<CONSTANT_Integer*>(slot);
                break;
            }
            case T_Double:{
                slot = new CONSTANT_Double();
                u4 highbyte;
                u4 lowbyte;
                highbyte = reader.readU4();
                lowbyte = reader.readU4();
                u8 val = (((int64_t)highbyte)<<32) + lowbyte;
                dynamic_cast<CONSTANT_Double*>(slot)->bytes = val;
                dynamic_cast<CONSTANT_Double*>(slot)->val = *(double*)&val;
                //delete(&highbyte);
                //delete(&lowbyte);
                file.constantPoolInfo[i] = dynamic_cast<CONSTANT_Double*>(slot);
                break;
            }
            case T_Float:{
                slot = new CONSTANT_Float();
                dynamic_cast<CONSTANT_Float*>(slot)->bytes= reader.readU4();
                dynamic_cast<CONSTANT_Float*>(slot)->val = *(float*) dynamic_cast<CONSTANT_Float*>(slot)->bytes;
                file.constantPoolInfo[i]= dynamic_cast<CONSTANT_Float*>(slot);
                break;
            }
            case T_Long:{
                slot = new CONSTANT_Long();
                u4 highbyte;
                u4 lowbyte;
                highbyte = reader.readU4();
                lowbyte = reader.readU4();
                u8 val = (((int64_t)highbyte)<<32) + lowbyte;
                dynamic_cast<CONSTANT_Long*>(slot)->bytes=val;
                dynamic_cast<CONSTANT_Long*>(slot)->val=*(long*)&val;
                file.constantPoolInfo[i] = dynamic_cast<CONSTANT_Long*>(slot);
                break;
            }
            case T_Utf8:{
                slot = new CONSTANT_Utf8_info();
                u2 len = reader.readU2();
                dynamic_cast<CONSTANT_Utf8_info*>(slot)->length = len;
                dynamic_cast<CONSTANT_Utf8_info*>(slot)->bytes = new u1[len+1];
                for(int i=0;i<len;i++){
                    dynamic_cast<CONSTANT_Utf8_info*>(slot)->bytes[i] = reader.readU1();
                }
                dynamic_cast<CONSTANT_Utf8_info*>(slot)->bytes[len]= '\0';
                file.constantPoolInfo[i]= dynamic_cast<CONSTANT_Utf8_info*>(slot);
                //cout<<"constantpool UTF8: "<<dynamic_cast<CONSTANT_Utf8_info*>(slot)->bytes<<endl;
                break;
            }
            case T_Fieldref:{
                slot = new CONSTANT_Fieldref();
                dynamic_cast<CONSTANT_Fieldref*>(slot)->classIndex =reader.readU2();
                dynamic_cast<CONSTANT_Fieldref*>(slot)->nameAndTypeIndex=reader.readU2();
                file.constantPoolInfo[i] = dynamic_cast<CONSTANT_Fieldref*>(slot);
                break;
            }
            case T_InterfaceMethodref:{
                slot = new CONSTANT_InterfaceMethodref();
                dynamic_cast<CONSTANT_InterfaceMethodref*>(slot)->interfaceIndex = reader.readU2();
                dynamic_cast<CONSTANT_InterfaceMethodref*>(slot)->nameAndTypeIndex = reader.readU2();
                break;
            }
            case T_InvokeDynamic:{
                slot = new CONSTANT_InvokeDynamic();
                dynamic_cast<CONSTANT_InvokeDynamic*>(slot)->bootstrapMethodAttrIndex=reader.readU2();
                dynamic_cast<CONSTANT_InvokeDynamic*>(slot)->nameAndTypeIndex = reader.readU2();
                file.constantPoolInfo[i] = dynamic_cast<CONSTANT_InvokeDynamic*>(slot);
                break;
            }
            case T_MethodHandle:{
                slot = new CONSTANT_MethodHandle();
                dynamic_cast<CONSTANT_MethodHandle*>(slot)->referenceIndex = reader.readU2();
                dynamic_cast<CONSTANT_MethodHandle*>(slot)->referenceKind = reader.readU2();
                file.constantPoolInfo[i] = dynamic_cast<CONSTANT_MethodHandle*>(slot);
                break;
            }
            case T_Methodref:{
                slot = new CONSTANT_Methodref();
                dynamic_cast<CONSTANT_Methodref*>(slot)->methodIndex=reader.readU2();
                dynamic_cast<CONSTANT_Methodref*>(slot)->nameAndTypeIndex=reader.readU2();
                file.constantPoolInfo[i] = dynamic_cast<CONSTANT_Methodref*>(slot);
                break;
            }
            case T_MethodType:{
                slot = new CONSTANT_MethodType();
                dynamic_cast<CONSTANT_MethodType*>(slot)->descriptorIndex=reader.readU2();
                file.constantPoolInfo[i] = dynamic_cast<CONSTANT_MethodType*>(slot);
                break;
            }
            case T_NameAndType:{
                slot = new CONSTANT_NameAndType();
                dynamic_cast<CONSTANT_NameAndType*>(slot)->nameAndTypeIndex=reader.readU2();
                dynamic_cast<CONSTANT_NameAndType*>(slot)->descriptionIndex= reader.readU2();
                file.constantPoolInfo[i]= dynamic_cast<CONSTANT_NameAndType*>(slot);
                break;
            }
            case T_String:{
                slot = new CONSTANT_String();
                dynamic_cast<CONSTANT_String*>(slot)->stringIndex=reader.readU2();
                file.constantPoolInfo[i]= dynamic_cast<CONSTANT_String*>(slot);
                break;
            }
            default:{
                std::cout<<"not support this constant type"<<endl;
            }
        }
    }
}

void JavaClass::parseInterface(u2 interface_count) {
    file.interfaces = new u2[interface_count];
    for(int i = 0;i < interface_count;i++){
        file.interfaces[i] = reader.readU2();
        cout<<"interfaces: "<<file.interfaces[i]<<endl;
    }
}

void JavaClass::parseFields(u2 fields_count) {
     file.fields = new FieldInfo[fields_count];
     for(int i=0;i<fields_count;i++){
         file.fields[i].accessFlags=reader.readU2();
         file.fields[i].nameIndex = reader.readU2();
         file.fields[i].descriptorIndex = reader.readU2();
         file.fields[i].attributeCount=reader.readU2();
     }
}bool JavaClass::parseMethod(u2 methods_Count) {
    file.methods = new MethodInfo[methods_Count];
    if (!file.methods) {
        cerr << __func__ << ":Can not allocate memory to load class file\n";
        return false;
    }

    FOR_EACH(i, file.methodsCount) {
        file.methods[i].accessFlags = reader.readU2();
        file.methods[i].nameIndex = reader.readU2();
        file.methods[i].descriptorIndex = reader.readU2();
        file.methods[i].attributeCount = reader.readU2();
        parseAttribute(file.methods[i].attributes,
                       file.methods[i].attributeCount);
    }
    return true;
}

void JavaClass::parseAttribute(AttributeInfo** (&attrs),u2 attr_count) {
      attrs = new(std::nothrow) AttributeInfo*[attr_count];

      if(attrs == nullptr){
          cerr << "new Attr** error"<< endl;
          return;
      }

      for(uint16_t i=0;i<attr_count;i++){
          const u2 attrStringIndex = reader.readU2();
          if (typeid(*file.constantPoolInfo[attrStringIndex]) != typeid(CONSTANT_Utf8_info)){
              cout<<"attr type error"<<endl;
              return;
          }
          char* attrName = (char*) dynamic_cast<CONSTANT_Utf8_info*>
                  (file.constantPoolInfo[attrStringIndex])->bytes;
           IS_ATTR_Code(attrName){
               auto* attribute = new ATTR_Code;
               attribute->attributeNameIndex=attrStringIndex;
               attribute->attributeLength= reader.readU4();
               attribute->maxStack = reader.readU2();
               attribute->maxLocals = reader.readU2();
               attribute->codeLen = reader.readU4();

               attribute->code = new u1[attribute->codeLen];
               FOR_EACH(a,attribute->codeLen){attribute->code[i] = reader.readU1();}
               attribute->exceptionTableLength=reader.readU2();
               attribute->exceptionTable= new Exceptions[attribute->exceptionTableLength];
               FOR_EACH(a,attribute->exceptionTableLength){
                   attribute->exceptionTable[a].startPC=reader.readU2();
                   attribute->exceptionTable[a].endPC=reader.readU2();
                   attribute->exceptionTable[a].handlerPC =reader.readU2();
                   attribute->exceptionTable[a].catchType =reader.readU2();
               }

               attribute->attributeCount=reader.readU2();
               parseAttribute(attribute->attributes,attribute->attributeCount);

               attrs[i]  = attribute;
               continue;
           }

          IS_ATTR_ConstantValue(attrName) {
              auto* attr = new ATTR_ConstantValue;
              attr->attributeNameIndex = attrStringIndex;
              attr->attributeLength = reader.readU4();
              attr->constantValueIndex = reader.readU2();

              attrs[i] = attr;
              continue;
          }
          if(strcmp(attrName,"StackMapTable")==0){
             auto* a = new ATTR_StackMapTable();
             a->attributeNameIndex = attrStringIndex;
             a->attributeLength =reader.readU4();
             a->num_of_entries = reader.readU2();
             a->entries = new stack_map_frame*[a->num_of_entries];
             for(int b=0;b<a->num_of_entries;b++){
                 u1 frame_type = reader.readU1();
                 if(IS_STACKFRAME_same_frame(frame_type)){
                     auto* frame = new stack_map_frame_same_frame();
                     a->entries[b] = frame;
                 }
                 if(IS_STACKFRAME_same_locals_1_stack_item_frame(frame_type)){
                     auto* frame = new same_locals_1_stack_item_frame();
                     frame->stack = new VerificationTypeInfo*[1];
                     frame->stack[0] = parseVerificationType(reader.readU1());
                     a->entries[b] = frame;
                 }
                 if(IS_STACKFRAME_same_locals_1_stack_item_frame_extended(frame_type)){
                     auto* frame = new same_locals_1_stack_item_extended();
                     frame->offset_delta=reader.readU2();
                     frame->stack = new VerificationTypeInfo*[1];
                     frame->frame_type = reader.readU1();
                     frame->stack[0] = parseVerificationType(frame->frame_type);
                     a->entries[b]=frame;
                 }
                 if(IS_STACKFRAME_same_frame_extended(frame_type)){
                     auto* frame = new same_frame_extended();
                     frame->offset_delta = reader.readU2();
                     a->entries[b] = frame;
                 }
                 if(IS_STACKFRAME_chop_frame(frame_type)){
                     auto* frame = new chop_frame;
                     frame->offset_delta = reader.readU2();
                     a->entries[b] = frame;
                 }
                 if(IS_STACKFRAME_append_frame(frame_type)){
                     auto* frame = new append_frame;
                     frame->frame_type = frame_type;
                     // It's important to store current frame type since
                     // ~Frame_Append need it to release memory
                     frame->offset_delta = reader.readU2();
                     frame->locals = new VerificationTypeInfo*[frame_type - 251];
                     FOR_EACH(p, frame_type - 251) {
                         frame->locals[p] =
                                 parseVerificationType(reader.readU1());
                     }
                     a->entries[b] = frame;
                 }
                 if(IS_STACKFRAME_full_frame(frame_type)){
                     auto* frame = new full_frame;
                     frame->offset_delta=reader.readU2();
                     frame->number_of_locals=reader.readU2();
                     frame->locals = new VerificationTypeInfo*[frame->number_of_locals];
                     FOR_EACH(c,frame->number_of_locals){
                         frame->locals[c]=parseVerificationType(reader.readU1());
                     }
                     frame->number_of_stacks=reader.readU2();
                     frame->stack=new VerificationTypeInfo*[frame->number_of_stacks];
                     FOR_EACH(c,frame->number_of_stacks){
                         frame->stack[c]=parseVerificationType(reader.readU1());
                     }
                     a->entries[b]=frame;
                 }
             }
              attrs[i]=a;
              continue;
          }
          /////////////////////////////////////////////
          IS_ATTR_Exceptions(attrName){
              auto* attr = new ATTR_Exception();
              attr->attributeNameIndex = attrStringIndex;
              attr->attributeLength = reader.readU4();
              attr->num_of_exceptions = reader.readU2();
              attr->exception_index_table = new u2[attr->num_of_exceptions];
              FOR_EACH(c,attr->num_of_exceptions){
                  attr->exception_index_table[c] = reader.readU2();
              }
              attrs[i] = attr;
              continue;
          }
          IS_ATTR_InnerClasses(attrName){
              auto* attr = new ATTR_InnerClasses;
              attr->attributeNameIndex = attrStringIndex;
              attr->attributeLength = reader.readU4();
              attr->numberOfClasses = reader.readU2();
              attr->classes =
                      new ATTR_InnerClasses::_classes[attr->numberOfClasses];
              FOR_EACH(k, attr->numberOfClasses) {
                  attr->classes[k].innerClassInfoIndex = reader.readU2();
                  attr->classes[k].outerClassInfoIndex = reader.readU2();
                  attr->classes[k].innerNameIndex = reader.readU2();
                  attr->classes[k].innerClassAccessFlags = reader.readU2();
              }
              attrs[i] = attr;
              continue;
          }
          IS_ATTR_EnclosingMethod(attrName) {
              auto* attr = new ATTR_EnclosingMethod;
              attr->attributeNameIndex = attrStringIndex;
              attr->attributeLength = reader.readU4();
              attr->classIndex = reader.readU2();
              attr->methodIndex = reader.readU2();
              attrs[i] = attr;
              continue;
          }
          IS_ATTR_Synthetic(attrName) {
              auto* attr = new ATTR_Synthetic;
              attr->attributeNameIndex = attrStringIndex;
              attr->attributeLength = reader.readU4();
              attrs[i] = attr;
              continue;
          }
          IS_ATTR_Signature(attrName){
              auto* attr = new ATTR_Signature;
              attr->attributeNameIndex = attrStringIndex;
              attr->attributeLength = reader.readU4();
              attr->signatureIndex=reader.readU2();
              continue;
          }
          IS_ATTR_SourceFile(attrName){
              auto* attr = new ATTR_SourceFile;
              attr->attributeNameIndex = attrStringIndex;
              attr->attributeLength = reader.readU4();
              attr->sourceFileIndex = reader.readU2();
              attrs[i] = attr;
              continue;
          }
          IS_ATTR_SourceDebugExtension(attrName) {
              auto* attr = new ATTR_SourceDebugExtension;
              attr->attributeNameIndex = attrStringIndex;
              attr->attributeLength = reader.readU4();
              attr->debugExtension = new u1[attr->attributeLength];
              FOR_EACH(k, attr->attributeLength) {
                  attr->debugExtension[k] = reader.readU1();
              }
              attrs[i] = attr;
              continue;
          }
          IS_ATTR_LineNumberTable(attrName) {
              auto* attr = new ATTR_LineNumberTable;
              attr->attributeNameIndex = attrStringIndex;
              attr->attributeLength = reader.readU4();
              attr->lineNumberTableLength = reader.readU2();
              attr->lineNumberTable = new ATTR_LineNumberTable::_lineNumberTable
              [attr->lineNumberTableLength];
              FOR_EACH(k, attr->lineNumberTableLength) {
                  attr->lineNumberTable[k].startPC = reader.readU2();
                  attr->lineNumberTable[k].lineNumber = reader.readU2();
              }
              attrs[i] = attr;
              continue;
          }
          IS_ATTR_LocalVariableTable(attrName) {
              auto* attr = new ATTR_LocalVariableTable;
              attr->attributeNameIndex = attrStringIndex;
              attr->attributeLength = reader.readU4();
              attr->localVariableTableLength = reader.readU2();
              attr->localVariableTable = new ATTR_LocalVariableTable::
              _localVariableTable[attr->localVariableTableLength];
              FOR_EACH(k, attr->localVariableTableLength) {
                  attr->localVariableTable[k].startPC = reader.readU2();
                  attr->localVariableTable[k].length = reader.readU2();
                  attr->localVariableTable[k].nameIndex = reader.readU2();
                  attr->localVariableTable[k].descriptorIndex = reader.readU2();
                  attr->localVariableTable[k].index = reader.readU2();
              }
              attrs[i] = attr;
              continue;
          }
          IS_ATTR_LocalVariableTypeTable(attrName) {
              auto* attr = new ATTR_LocalVariableTypeTable;
              attr->attributeNameIndex = attrStringIndex;
              attr->attributeLength = reader.readU4();
              attr->localVariableTypeTableLength = reader.readU2();
              attr->localVariableTypeTable = new ATTR_LocalVariableTypeTable::
              _localVariableTypeTable[attr->localVariableTypeTableLength];
              FOR_EACH(k, attr->localVariableTypeTableLength) {
                  attr->localVariableTypeTable[k].startPC = reader.readU2();
                  attr->localVariableTypeTable[k].length = reader.readU2();
                  attr->localVariableTypeTable[k].nameIndex = reader.readU2();
                  attr->localVariableTypeTable[k].signatureIndex =
                          reader.readU2();
                  attr->localVariableTypeTable[k].index = reader.readU2();
              }
              attrs[i] = attr;
              continue;
          }
          IS_ATTR_Deprecated(attrName) {
              auto* attr = new ATTR_Deprecated;
              attr->attributeNameIndex = attrStringIndex;
              attr->attributeLength = reader.readU4();
              attrs[i] = attr;
              continue;
          }
          IS_ATTR_RuntimeVisibleAnnotations(attrName) {
              auto* attr = new ATTR_RuntimeVisibleAnnotations;
              attr->attributeNameIndex = attrStringIndex;
              attr->attributeLength = reader.readU4();
              attr->numAnnotations = reader.readU2();
              attr->annotations = new Annotation[attr->numAnnotations];
              FOR_EACH(k, attr->numAnnotations) {
                  attr->annotations[k] = readToAnnotationStructure();
              }
              attrs[i] = attr;
              continue;
          }
          IS_ATTR_RuntimeInvisibleAnnotations(attrName) {
              auto* attr = new ATTR_RuntimeInvisibleAnnotations;
              attr->attributeNameIndex = attrStringIndex;
              attr->attributeLength = reader.readU4();
              attr->numAnnotations = reader.readU2();
              attr->annotations = new Annotation[attr->numAnnotations];
              FOR_EACH(k, attr->numAnnotations) {
                  attr->annotations[k] = readToAnnotationStructure();
              }
              attrs[i] = attr;
              continue;
          }
          IS_ATTR_RuntimeVisibleParameterAnnotations(attrName) {
              auto* attr = new ATTR_RuntimeVisibleParameterAnnotations;
              attr->attributeNameIndex = attrStringIndex;
              attr->attributeLength = reader.readU4();
              attr->numParameters = reader.readU1();
              attr->parameterAnnotations =
                      new ATTR_RuntimeVisibleParameterAnnotations::
                      _parameterAnnotations[attr->numParameters];
              FOR_EACH(k, attr->numParameters) {
                  attr->parameterAnnotations[k].numAnnotations =
                          reader.readU2();
                  attr->parameterAnnotations[k].annotations =
                          new Annotation[attr->parameterAnnotations[k]
                                  .numAnnotations];
                  FOR_EACH(p, attr->parameterAnnotations[k].numAnnotations) {
                      attr->parameterAnnotations[k].annotations[p] =
                              readToAnnotationStructure();
                  }
              }
              attrs[i] = attr;
              continue;
          }
          IS_ATTR_RuntimeInvisibleParameterAnnotations(attrName) {
              auto* attr = new ATTR_RuntimeInvisibleParameterAnnotations;
              attr->attributeNameIndex = attrStringIndex;
              attr->attributeLength = reader.readU4();
              attr->numParameters = reader.readU1();
              attr->parameterAnnotations =
                      new ATTR_RuntimeInvisibleParameterAnnotations::
                      _parameterAnnotations[attr->numParameters];
              FOR_EACH(k, attr->numParameters) {
                  attr->parameterAnnotations[k].numAnnotations =
                          reader.readU2();
                  attr->parameterAnnotations[k].annotations =
                          new Annotation[attr->parameterAnnotations[k]
                                  .numAnnotations];
                  FOR_EACH(p, attr->parameterAnnotations[k].numAnnotations) {
                      attr->parameterAnnotations[k].annotations[p] =
                              readToAnnotationStructure();
                  }
              }
              attrs[i] = attr;
              continue;
          }
          IS_ATTR_RuntimeVisibleTypeAnnotations(attrName) {
              auto* attr = new ATTR_RuntimeVisibleTypeAnnotations;
              attr->attributeNameIndex = attrStringIndex;
              attr->attributeLength = reader.readU4();
              attr->numAnnotations = reader.readU2();
              attr->annotations = new TypeAnnotation[attr->numAnnotations];
              FOR_EACH(k, attr->numAnnotations) {
                  attr->annotations[k].targetType = reader.readU1();
                  attr->annotations[k].targetInfo =
                          determineTargetType(attr->annotations[k].targetType);

                  // read to target_path
                  attr->annotations[k].targetPath.pathLength = reader.readU1();
                  attr->annotations[k].targetPath.path = new TypeAnnotation::
                  TypePath::_path[attr->annotations[k].targetPath.pathLength];
                  FOR_EACH(p, attr->annotations[k].targetPath.pathLength) {
                      attr->annotations[k].targetPath.path[p].typePathKind =
                              reader.readU1();
                      attr->annotations[k].targetPath.path[p].typeArgumentIndex =
                              reader.readU1();
                  }

                  attr->annotations[k].typeIndex = reader.readU2();
                  attr->annotations[k].numElementValuePairs = reader.readU2();
                  attr->annotations[k].elementValuePairs =
                          new TypeAnnotation::_elementValuePairs
                          [attr->annotations[k].numElementValuePairs];
                  FOR_EACH(p, attr->annotations[k].numElementValuePairs) {
                      attr->annotations[k].elementValuePairs[p].elementNameIndex =
                              reader.readU2();
                      attr->annotations[k].elementValuePairs[p].value =
                              readToElementValueStructure();
                  }
              }
              attrs[i] = attr;
              continue;
          }
          IS_ATTR_RuntimeInvisibleTypeAnnotations(attrName) {
              auto* attr = new ATTR_RuntimeInvisibleTypeAnnotations;
              attr->attributeNameIndex = attrStringIndex;
              attr->attributeLength = reader.readU4();
              attr->numAnnotations = reader.readU2();
              attr->annotations = new TypeAnnotation[attr->numAnnotations];
              FOR_EACH(k, attr->numAnnotations) {
                  attr->annotations[k].targetType = reader.readU1();
                  attr->annotations[k].targetInfo =
                          determineTargetType(attr->annotations[k].targetType);

                  // read to target_path
                  attr->annotations[k].targetPath.pathLength = reader.readU1();
                  attr->annotations[k].targetPath.path = new TypeAnnotation::
                  TypePath::_path[attr->annotations[k].targetPath.pathLength];
                  FOR_EACH(p, attr->annotations[k].targetPath.pathLength) {
                      attr->annotations[k].targetPath.path[p].typePathKind =
                              reader.readU1();
                      attr->annotations[k].targetPath.path[p].typeArgumentIndex =
                              reader.readU1();
                  }

                  attr->annotations[k].typeIndex = reader.readU2();
                  attr->annotations[k].numElementValuePairs = reader.readU2();
                  attr->annotations[k].elementValuePairs =
                          new TypeAnnotation::_elementValuePairs
                          [attr->annotations[k].numElementValuePairs];
                  FOR_EACH(p, attr->annotations[k].numElementValuePairs) {
                      attr->annotations[k].elementValuePairs[p].elementNameIndex =
                              reader.readU2();
                      attr->annotations[k].elementValuePairs[p].value =
                              readToElementValueStructure();
                  }
              }
              attrs[i] = attr;
              continue;
          }
          IS_ATTR_AnnotationDefault(attrName) {
              auto* attr = new ATTR_AnnotationDefault;
              attr->attributeNameIndex = attrStringIndex;
              attr->attributeLength = reader.readU4();
              attr->defaultValue = readToElementValueStructure();
              attrs[i] = attr;
              continue;
          }
          IS_ATTR_BootstrapMethods(attrName) {
              auto* attr = new ATTR_BootstrapMethods;
              attr->attributeNameIndex = attrStringIndex;
              attr->attributeLength = reader.readU4();
              attr->numBootstrapMethods = reader.readU2();
              attr->bootstrapMethod = new ATTR_BootstrapMethods::_bootstrapMethod
              [attr->numBootstrapMethods];
              FOR_EACH(k, attr->numBootstrapMethods) {
                  attr->bootstrapMethod[k].bootstrapMethodRef = reader.readU2();

                  attr->bootstrapMethod[k].numBootstrapArgument =
                          reader.readU2();
                  attr->bootstrapMethod[k].bootstrapArguments =
                          new u2[attr->bootstrapMethod[k].numBootstrapArgument];
                  FOR_EACH(p, attr->bootstrapMethod[k].numBootstrapArgument) {
                      attr->bootstrapMethod[k].bootstrapArguments[p] =
                              reader.readU2();
                  }
              }
              attrs[i] = attr;
              continue;
          }
          IS_ATTR_MethodParameters(attrName) {
              auto* attr = new ATTR_MethodParameter;
              attr->attributeNameIndex = attrStringIndex;
              attr->attributeLength = reader.readU4();
              attr->parameterCount = reader.readU1();
              attr->parameters =
                      new ATTR_MethodParameter::_parameters[attr->parameterCount];
              FOR_EACH(k, attr->parameterCount) {
                  attr->parameters[k].nameIndex = reader.readU2();
                  attr->parameters[k].accessFlags = reader.readU2();
              }
              attrs[i] = attr;
          }
      }
}


VerificationTypeInfo *JavaClass::parseVerificationType(u1 tag) {
    switch (tag) {
        case ITEM_Top: {
            return new VariableInfo_Top();
        }
        case ITEM_Integer: {
            return new VariableInfo_Integer;
        }
        case ITEM_Float: {
            return new VariableInfo_Float;
        }
        case ITEM_Null: {
            return new VariableInfo_Null;
        }
        case ITEM_UninitializedThis: {
            return new VariableInfo_UninitializedThis;
        }
        case ITEM_Object: {
            auto* x = new VariableInfo_Object;
            x->cpIndex = reader.readU2();
            return x;
        }
        case ITEM_Uninitialized: {
            auto* x = new VariableInfo_Uninitialized;
            x->offset = reader.readU2();
            return x;
        }
        case ITEM_Long: {
            return new VariableInfo_Long;
        }
        case ITEM_Double: {
            return new VariableInfo_Double;
        }
        default:
            cerr << __func__ << ":Incorrect tag of verification type\n";
            return nullptr;
    }

}
Annotation JavaClass::readToAnnotationStructure() {
    Annotation a{};
    a.typeIndex = reader.readU2();
    a.numElementValuePairs = reader.readU2();
    FOR_EACH(p, a.numElementValuePairs) {
        a.elementValuePairs[p].elementNameIndex = reader.readU2();
        a.elementValuePairs[p].value = readToElementValueStructure();
    }
    return a;
}

ElementValue* JavaClass::readToElementValueStructure() {
    char tag = reader.readU1();
    switch (tag) {
        case 'B':
        case 'C':
        case 'D':
        case 'F':
        case 'I':
        case 'J':
        case 'S':
        case 'Z':
        case 's': {
            // const_value_index of union
            auto* e = new ElementValue_ConstantValueIndex;
            e->constValueIndex = reader.readU2();
            return e;
        }
        case 'e': {
            auto* e = new ElementValue_EnumConstValue;
            e->typeNameIndex = reader.readU2();
            e->constNameIndex = reader.readU2();
            break;
        }
        case 'c': {
            auto* e = new ElementValue_ClassInfoIndex;
            e->classInfoIndex = reader.readU2();
            return e;
        }
        case '@': {
            auto* e = new ElementValue_Annotation;
            e->annotationValue = readToAnnotationStructure();
            return e;
        }
        case '[': {
            auto* e = new ElementValue_ArrayValue;
            e->numValues = reader.readU2();
            e->values = new ElementValue*[e->numValues];
            FOR_EACH(i, e->numValues) {
                e->values[i] = readToElementValueStructure();
            }
            return e;
        }
        default:
            cerr << __func__ << ":Incorrect element value type\n";
            return nullptr;
    }
}
    TargetInfo* JavaClass::determineTargetType(u1 tag) {
        if (tag == 0x00 || tag == 0x01) {
            auto *t = new Target_TypeParameter;
            t->typeParameterIndex = reader.readU1();
            return t;
        }
        if (tag == 0x10) {
            auto *t = new Target_SuperType;
            t->superTypeIndex = reader.readU2();
            return t;
        }
        if (tag == 0x11 || tag == 0x12) {
            auto *t = new Target_TypeParameterBound;
            t->typeParameterIndex = reader.readU1();
            t->boundIndex = reader.readU1();
            return t;
        }
        if (tag == 0x13 || tag == 0x14 || tag == 0x15) {
            return new Target_Empty;
        }
        if (tag == 0x16) {
            auto *t = new Target_FormalParameter;
            t->formalParameter = reader.readU1();
            return t;
        }
        if (tag == 0x17) {
            auto *t = new Target_Throws;
            t->throwsTypeIndex = reader.readU2();
            return t;
        }
        if (tag == 0x40 || tag == 0x41) {
            auto *t = new Target_LocalVar;
            t->tableLength = reader.readU2();
            FOR_EACH(i, t->tableLength) {
                t->table[i].startPc = reader.readU2();
                t->table[i].length = reader.readU2();
                t->table[i].index = reader.readU2();
            }
            return t;
        }
        if (tag == 0x42) {
            auto *t = new Target_Catch;
            t->exceptionTableIndex = reader.readU2();
            return t;
        }
        if (tag >= 0x43 && tag <= 0x46) {
            auto *t = new Target_Offset;
            t->offset = reader.readU2();
            return t;
        }
        if (tag >= 0x47 && tag <= 0x4B) {
            auto *t = new Target_TypeArgument;
            t->offset = reader.readU2();
            t->typeArgumentIndex = reader.readU1();
            return t;
        }
}

MethodInfo *JavaClass::findMethod(const string &methodName, const string &methodDescriptor) const {
    return nullptr;
}

JType *JavaClass::getStaticVar(const string &name, const string &descriptor) {
    return nullptr;
}

bool JavaClass::setStaticVar(const string &name, const string &descriptor, JType *value) {
    return false;
}
