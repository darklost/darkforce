# 2014-12-24
# build by qianqians
# codegenclient

import os
import argvs

def maketypegetvalue(type):
    if type == 'int':
        return 'int64_t'
    if type == 'float':
        return 'double'
    if type == 'bool':
        return 'bool'
    if type == 'string' or type == 'std::string':
        return 'std::sstring'

def  maketype(type, name):
    if type == 'int':
        return '	n.' + name + ' = ' + 'boost::any_cast<int64_t>((*r)[\"ret\"][' + name + ']);'
    if type == 'float':
        return '	n.' + name + ' = ' + 'boost::any_cast<double>((*r)[\"ret\"][' + name + ']);'
    if type == 'bool':
        return '	n.' + name + ' = ' + 'boost::any_cast<bool>((*r)[\"ret\"][' + name + ']);'
    if type == 'string' or type == 'std::string':
        return '	n.' + name + ' = ' + 'boost::any_cast<std::string>((*r)[\"ret\"][' + name + ']);'
    if type == 'array':
        code = '	for(int i = 0; i < (*r)[\"ret\"].size(); i++){\n'
        code += '		n.' + name + '.push_back(boost::any_cast<' + maketypegetvalue(type) + '>((*r)[\"ret\"][i]));'
        code += '}\n'
        return code

def unpackstruct(type, struct):
    for k, v in struct:
        for name, define in v:
            if type == name:
                code = '	name n;\n'
                for argv in define:
                    code += maketype(argv[0], argv[1])
                code += '	return n;'
                return code

def makearray(type):
    indexb = type.find('<')
    indexe = type.find('>')
    templatetype = type[indexb + 1 : indexe]
    if templatetype == 'int':
        return 'std::vector<int64_t> v;\n' \
               'for(int i = 0; i < (*r)[\"ret\"].size(); i++){\n' \
               '	v.push_back(boost::any_cast<int64_t>((*r)[\"ret\"][i]));\n' \
               '}\n' \
               'return v;'
    if templatetype == 'float':
        return 'std::vector<double> v;\n' \
               'for(int i = 0; i < (*r)[\"ret\"].size(); i++){\n' \
               '	v.push_back(boost::any_cast<double>((*r)[\"ret\"][i]));\n' \
               '}\n' \
               'return v;'
    if templatetype == 'bool':
        return 'std::vector<bool> v;\n' \
               'for(int i = 0; i < (*r)[\"ret\"].size(); i++){\n' \
               '	v.push_back(boost::any_cast<bool>((*r)[\"ret\"][i]));\n' \
               '}\n' \
               'return v;'
    if templatetype == 'string' or type == 'std::string':
        return 'std::vector<std::string> v;\n' \
               'for(int i = 0; i < (*r)[\"ret\"].size(); i++){\n' \
               '	v.push_back(boost::any_cast<std::string>((*r)[\"ret\"][i]));\n' \
               '}\n' \
               'return v;'

def makeret(type, struct):
    if type == 'int':
        return 'boost::any_cast<int64_t>((*r)[\"ret\"]);'
    if type == 'float':
        return 'boost::any_cast<double>((*r)[\"ret\"]);'
    if type == 'bool':
        return 'boost::any_cast<bool>((*r)[\"ret\"]);'
    if type == 'string' or type == 'std::string':
        return 'boost::any_cast<std::string>((*r)[\"ret\"]);'
    if type.find('array') != -1:
        return makearray(type)
    if type == 'map':
        return '(*r)[\"ret\"];'
    if type == 'void':
        return ''
    else:
        return unpackstruct(type, struct)

def  maketypevalue(type, name):
    if type == 'int':
        return '	n.' + name + ' = ' + 'boost::any_cast<int64_t>((*v)[' + name + ']' + ');'
    if type == 'float':
        return '	n.' + name + ' = ' + 'boost::any_cast<double>((*v)[' + name + ']' + ');'
    if type == 'bool':
        return '	n.' + name + ' = ' + 'boost::any_cast<bool>((*v)[' + name + ']' + ');'
    if type == 'string' or type == 'std::string':
        return '	n.' + name + ' = ' + 'boost::any_cast<std::string>((*v)[' + name + ']' + ');'
    if type.find('array') != -1:
        indexb = type.find('<')
        indexe = type.find('>')
        templatetype = type[indexb + 1 : indexe]
        code = '	n.' + name + ';\n'
        code += '	for(int i = 0; i < (*v).size(); i++){\n'
        code += '		n.' + name + '.push_back(boost::any_cast<' + maketypegetvalue(templatetype) + '>((*v)[i]));'
        code += '}\n'
        return code

def unpackstructvalue(type, name, struct):
    for k, v in struct:
        for typename, define in v:
            if type == typename:
                code = '	typename ' + name + ';\n'
                for argv in define:
                    code += maketypevalue(argv[0], argv[1])
                return code

def makearrayvalue(type, name):
    indexb = type.find('<')
    indexe = type.find('>')
    templatetype = type[indexb + 1 : indexe]
    if templatetype == 'int':
        return '		std::vector<int64_t> ' + name + ';\n' \
               '		for(int i = 0; i < (*v)[\"' + name + '\"].size(); i++){\n' \
               '			v.push_back(boost::any_cast<int64_t>((*v)[\"' + name + '\"][i]));\n' \
               '		}\n'
    if templatetype == 'float':
        return '		std::vector<double> ' + name + ';\n' \
               '		for(int i = 0; i < (*v)[\"' + name + '\"].size(); i++){\n' \
               '			v.push_back(boost::any_cast<double>((*v)[\"' + name + '\"][i]));\n' \
               '		}\n'
    if templatetype == 'bool':
        return '		std::vector<bool> ' + name + ';\n' \
               '		for(int i = 0; i < (*v)[\"' + name + '\"].size(); i++){\n' \
               '			v.push_back(boost::any_cast<bool>((*v)[\"' + name + '\"]));\n' \
               '		}\n'
    if templatetype == 'string' or templatetype == 'std::string':
        return '		std::vector<std::string> ' + name + ';\n' \
               '		for(int i = 0; i < (*v)[\"' + name + '\"].size(); i++){\n' \
               '			v.push_back(boost::any_cast<std::string>((*v)[\"' + name + '\"][i]));\n' \
               '		}\n'

def makevalue(type, name, struct):
    if type == 'int':
        return '		auto ' + name + ' = boost::any_cast<int64_t>((*v)[\"' + name + '\"]);\n'
    if type == 'float':
        return '		auto ' + name + ' = boost::any_cast<double>((*v)[\"' + name + '\"]);\n'
    if type == 'bool':
        return '		auto ' + name + ' = boost::any_cast<bool>((*v)[\"' + name + '\"]);\n'
    if type == 'string' or type == 'std::string':
        return '		auto ' + name + ' = boost::any_cast<std::string>((*v)[\"' + name + '\"]);\n'
    if type.find('array') != -1:
        return makearrayvalue(type, name)
    if type == 'map':
        return '		auto ' + name + ' = (*v)[\"' + name + '\"];\n'
    else:
        return unpackstructvalue(type, name, struct)

def typetocpptype(type):
    if type == 'int':
        return 'int64_t'
    if type == 'float':
        return 'double'
    if type == 'string':
        return 'std::string'
    return type

def makearraytocpp(type, name):
    indexb = type.find('<')
    indexe = type.find('>')
    templatetype = type[indexb + 1 : indexe]
    return '	' + 'std::vector<' + typetocpptype(templatetype) + '> ' + name + ';'

def maketypetocpptype(type):
    if type.find('array') != -1:
        indexb = type.find('<')
        indexe = type.find('>')
        templatetype = type[indexb + 1 : indexe]
        return 'std::vector<' + typetocpptype(templatetype) + '> '
    if type == 'int':
        return 'int64_t'
    if type == 'float':
        return 'double'
    if type == 'string':
        return 'std::string'
    return type