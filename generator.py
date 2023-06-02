#! /bin/python3

from pathlib  import Path
from argparse import ArgumentParser
from typing   import List, Tuple

class expression_class_file:
    def __init__(self, class_name: str, arg_list: List[Tuple[str, str]], header_file: Path, source_file: Path):
        self._class_name = f'{class_name}'
        self._header_file = header_file
        self._source_file = source_file
        self._arg_list = arg_list

        self._gen_arg_strings()

    def class_name(self) -> str:
        return self._class_name
    
    def header_path(self) -> Path:
        return self._header_file

    def _gen_arg_strings(self) -> None:
        self._arg_strings = []
        for a in self._arg_list:
            self._arg_strings.append(f'std::shared_ptr<{a[0]}> {a[1]}')

    def _gen_header(self) -> None:
        header_text = f"""
/**
 * This file is generated by {__file__}. Make changes there and not to this file directly. 
 */

#ifndef {self._class_name.upper()}_H
#define {self._class_name.upper()}_H

#include <string>
#include <memory>

#include "expression/expression.h"
"""
        for a in self._arg_list:
            if a[0] == 'token':
                header_text += '#include "tokens/token.h"\n'
            elif a[0] == 'object':
                header_text += '#include "types/object.h"\n'

        header_text += f'\nclass {self._class_name}: public expression\n'
        header_text += '{\n\npublic:\n\n'
        header_text += f'    {self._class_name}('

        for i in range(len(self._arg_strings)):
            header_text += self._arg_strings[i]
            if i + 1 < len(self._arg_strings):
                header_text += ', '  
        header_text += ');'  
        header_text += f"""
    {self._class_name}(const {self._class_name} &other);
    ~{self._class_name}(); 

    virtual std::shared_ptr<object> accept(expressionvisitor &visitor);
    
    virtual std::string to_string() const; 
    virtual std::string type_name() const;  
     
"""
        for astring in self._arg_strings:
            header_text += f'    {astring};\n'
        header_text += '\n};\n\n#endif\n'
        
        with open(self._header_file, 'w') as header:
            header.write(header_text)

    def _gen_source(self) -> None:
        source_text = f"""
/**
 * This file is generated by {__file__}. Make changes there and not to this file directly. 
 */

#include <sstream>

#include "{self._header_file}"
#include "generated/expression/expressionvisitor.h"

{self._class_name}::{self._class_name}("""


        for i in range(len(self._arg_strings)):
            source_text += self._arg_strings[i]
            if i + 1 < len(self._arg_strings):
                source_text += ', ' 
        source_text += '):\n'         
        for i in range(len(self._arg_list)):
            source_text += f'    {self._arg_list[i][1]}({self._arg_list[i][1]})'
            if i + 1 < len(self._arg_list):
                source_text += ','
            source_text += '\n' 
        source_text += '{\n\n}\n\n'
        source_text += f'{self._class_name}::{self._class_name}(const {self._class_name} &other):\n'
        for i in range(len(self._arg_list)):
            source_text += f'    {self._arg_list[i][1]}(other.{self._arg_list[i][1]})'
            if i + 1 < len(self._arg_list):
                source_text += ','
            source_text += '\n'  
        source_text += '{\n\n}\n\n'   
        source_text += f'{self._class_name}::~{self._class_name}()\n'
        source_text += '{\n\n}\n\n'       


        source_text += f"""
std::shared_ptr<object> {self._class_name}::accept(expressionvisitor &visitor)        
"""
        source_text += '{'
        source_text += f"""
    return visitor.visit_{self._class_name}(this);
"""
        source_text += '}\n\n'        
        source_text += f'std::string {self._class_name}::to_string() const\n' 
        source_text += """{
    std::stringstream stream;
    stream <<"""
        
        for i in range(len(self._arg_list)):
            source_text += f' *(this->{self._arg_list[i][1]})'
            if i + 1 < len(self._arg_list):
                source_text += '<< " " <<'
        source_text += ';'          

        source_text += """
    return stream.str();
}

"""

        source_text += f'std::string {self._class_name}::type_name() const\n'
        source_text += '{\n'
        source_text += f'    return "{self._class_name}";\n'
        source_text += '}\n'  

        with open(self._source_file, 'w') as source:
            source.write(source_text)

    def __str__(self):
        return f'{self._class_name}:\n\t{self._header_file}\n\t{self._source_file}' 
    
    def check_time(self, mtime:float) -> bool:
        if not self._header_file.exists():
            return True
        elif self._header_file.stat().st_mtime < mtime:
            return True
        elif not self._source_file.exists():
            return True
        elif self._source_file.stat().st_mtime < mtime:
            return True
        return False
    
    def write(self) -> None:
        if self._header_file.exists():
            self._header_file.unlink()
        if self._source_file.exists():
            self._source_file.unlink()
        self._gen_header()
        self._gen_source()

class expression_visitor_file(expression_class_file):
    def __init__(self, class_name: str, header_file: Path, source_file: Path):
        super().__init__(class_name, [], header_file, source_file)
        self._to_visit = []

    def add_to_visit(self, to_visit_name: str, header_file: Path) -> None:
        self._to_visit.append((to_visit_name, header_file))

    def _gen_arg_strings(self) -> None:
        pass

    def _gen_header(self) -> None:
        header_text = f"""
/**
 * This file is generated by {__file__}. Make changes there and not to this file directly. 
 */

#ifndef {self._class_name.upper()}_H
#define {self._class_name.upper()}_H

#include <memory>

#include "types/object.h"
"""
        for t in self._to_visit:
            header_text += f'#include "{t[1]}"\n'
        
        header_text += f"""

class {self._class_name}
"""
        header_text += "{\n\npublic:\n"

        header_text += f'    {self._class_name}()' + ' { }\n'
        header_text += f'    ~{self._class_name}()' + ' { }\n'
        for t in self._to_visit:
            header_text += f'    virtual std::shared_ptr<object> visit_{t[0]}({t[0]} *to_visit) = 0;\n'
        header_text += f"""
"""
        header_text += "};\n\n"
        header_text += f"""
#endif        
"""
        with open(self._header_file, 'w') as header:
            header.write(header_text)

    def _gen_source(self) -> None:
        pass

class statement_class_file:
    def __init__(self, class_name: str, arg_list: List[Tuple[str, str]], header_file: Path, source_file: Path):
        self._class_name = f'{class_name}'
        self._header_file = header_file
        self._source_file = source_file
        self._arg_list = arg_list

        self._gen_arg_strings()

    def class_name(self) -> str:
        return self._class_name
    
    def header_path(self) -> Path:
        return self._header_file

    def _gen_arg_strings(self) -> None:
        self._arg_strings = []
        for a in self._arg_list:
            self._arg_strings.append(f'std::shared_ptr<{a[0]}> {a[1]}')

    def __str__(self):
        return f'{self._class_name}:\n\t{self._header_file}\n\t{self._source_file}'             

    def check_time(self, mtime:float) -> bool:
        if not self._header_file.exists():
            return True
        elif self._header_file.stat().st_mtime < mtime:
            return True
        elif not self._source_file.exists():
            return True
        elif self._source_file.stat().st_mtime < mtime:
            return True
        return False
    
    def _gen_header(self) -> None:
        header_text = f"""
/**
 * This file is generated by {__file__}. Make changes there and not to this file directly. 
 */

#ifndef {self._class_name.upper()}_H
#define {self._class_name.upper()}_H

#include <string>
#include <memory>

#include "statement/statement.h"
"""
        for a in self._arg_list:
            if a[0] == 'token':
                header_text += '#include "tokens/token.h"\n'
            elif a[0] == 'object':
                header_text += '#include "types/object.h"\n'

        header_text += f'\nclass {self._class_name}: public statement\n'
        header_text += '{\n\npublic:\n\n'
        header_text += f'    {self._class_name}('

        for i in range(len(self._arg_strings)):
            header_text += self._arg_strings[i]
            if i + 1 < len(self._arg_strings):
                header_text += ', '  
        header_text += ');'  
        header_text += f"""
    {self._class_name}(const {self._class_name} &other);
    ~{self._class_name}(); 

    virtual std::shared_ptr<object> accept(statementvisitor &visitor);
    
    virtual std::string to_string() const; 
    virtual std::string type_name() const;  
     
"""
        for astring in self._arg_strings:
            header_text += f'    {astring};\n'
        header_text += '\n};\n\n#endif\n'

        with open(self._header_file, 'w') as header:
            header.write(header_text)


    def _gen_source(self) -> None:
        source_text = f"""
/**
 * This file is generated by {__file__}. Make changes there and not to this file directly. 
 */

#include <sstream>

#include "{self._header_file}"
#include "generated/statement/statementvisitor.h"

{self._class_name}::{self._class_name}("""

        for i in range(len(self._arg_strings)):
            source_text += self._arg_strings[i]
            if i + 1 < len(self._arg_strings):
                source_text += ', ' 
        source_text += '):\n'         
        for i in range(len(self._arg_list)):
            source_text += f'    {self._arg_list[i][1]}({self._arg_list[i][1]})'
            if i + 1 < len(self._arg_list):
                source_text += ','
            source_text += '\n' 
        source_text += '{\n\n}\n\n'
        source_text += f'{self._class_name}::{self._class_name}(const {self._class_name} &other):\n'
        for i in range(len(self._arg_list)):
            source_text += f'    {self._arg_list[i][1]}(other.{self._arg_list[i][1]})'
            if i + 1 < len(self._arg_list):
                source_text += ','
            source_text += '\n'  
        source_text += '{\n\n}\n\n'   
        source_text += f'{self._class_name}::~{self._class_name}()\n'
        source_text += '{\n\n}\n\n'   

        source_text += f"""
void {self._class_name}::accept(statementvisitor &visitor)        
"""
        source_text += '{'
        source_text += f"""
    visitor.visit_{self._class_name}(this);
"""
        source_text += '}\n\n'        
        source_text += f'std::string {self._class_name}::to_string() const\n' 
        source_text += """{
    std::stringstream stream;
    stream <<"""
        
        for i in range(len(self._arg_list)):
            source_text += f' *(this->{self._arg_list[i][1]})'
            if i + 1 < len(self._arg_list):
                source_text += '<< " " <<'
        source_text += ';'          

        source_text += """
    return stream.str();
}

"""
        source_text += f'std::string {self._class_name}::type_name() const\n'
        source_text += '{\n'
        source_text += f'    return "{self._class_name}";\n'
        source_text += '}\n'   

        with open(self._source_file, 'w') as source:
            source.write(source_text)

    def write(self):
        if self._header_file.exists():
            self._header_file.unlink()
        if self._source_file.exists():
            self._source_file.unlink()
        self._gen_header()
        self._gen_source()

class statement_visitor_file(statement_class_file):
    def __init__(self, class_name: str, header_file: Path, source_file: Path):
        super().__init__(class_name, [], header_file, source_file)
        self._to_visit = []

    def add_to_visit(self, to_visit_name: str, header_file: Path) -> None:
        self._to_visit.append((to_visit_name, header_file))

    def _gen_arg_strings(self) -> None:
        pass

    def _gen_header(self) -> None:
        header_text = f"""
/**
 * This file is generated by {__file__}. Make changes there and not to this file directly. 
 */

#ifndef {self._class_name.upper()}_H
#define {self._class_name.upper()}_H

#include <memory>

#include "types/object.h"
"""
        for t in self._to_visit:
            header_text += f'#include "{t[1]}"\n'
        
        header_text += f"""

class {self._class_name}
"""
        header_text += "{\n\npublic:\n"

        header_text += f'    {self._class_name}()' + ' { }\n'
        header_text += f'    ~{self._class_name}()' + ' { }\n'
        for t in self._to_visit:
            header_text += f'    virtual void visit_{t[0]}({t[0]} *to_visit) = 0;\n'
        header_text += f"""
"""
        header_text += "};\n\n"
        header_text += f"""
#endif        
"""
        with open(self._header_file, 'w') as header:
            header.write(header_text)

    def _gen_source(self) -> None:
        pass

def parse_expression(line: str, header_dir: Path, source_dir: Path) -> expression_class_file:
    line_data = line.split(':')
    class_name = line_data[0].strip() + 'expression'
    header_file = header_dir/f'{class_name}.h'
    source_file = source_dir/f'{class_name}.cpp'
    arg_list = []

    def_data = line_data[1].strip().split(',')
    def_data = [ arg.strip() for arg in def_data]
    for arg in def_data:
        a = arg.split(' ')
        arg_list.append((a[0].strip(), a[1].strip()))
    return expression_class_file(class_name, arg_list, header_file, source_file)

def parse_grammer_file(grammer_file: Path, header_dir: Path, source_dir: Path) -> List[expression_class_file]:
    ret = []
    visitor = expression_visitor_file('expressionvisitor', header_dir/'expressionvisitor.h', source_dir/'expressionvisitor.cpp')
    with open(grammer_file, 'r') as gf:
        for entry in gf:
            new_class = parse_expression(entry, header_dir, source_dir) 
            visitor.add_to_visit(new_class.class_name(), new_class.header_path())
            ret.append(new_class)
    ret.append(visitor)
    return ret

def parse_statement(line: str, header_dir: Path, source_dir: Path) -> statement_class_file:
    line_data = line.split(':')
    class_name = line_data[0].strip() + 'statement'
    header_file = header_dir/f'{class_name}.h'
    source_file = source_dir/f'{class_name}.cpp'
    arg_list = []

    def_data = line_data[1].strip().split(',')
    def_data = [ arg.strip() for arg in def_data]
    for arg in def_data:
        a = arg.split(' ')
        arg_list.append((a[0].strip(), a[1].strip()))
    return statement_class_file(class_name, arg_list, header_file, source_file)

def parse_statement_file(statement_file: Path, header_dir: Path, source_dir: Path) -> List[statement_class_file]:
    ret = []
    visitor = statement_visitor_file('statementvisitor', header_dir/'statementvisitor.h', source_dir/'statementvisitor.cpp')
    with open(statement_file, 'r') as sf:
        for entry in sf:
            new_class = parse_statement(entry, header_dir, source_dir) 
            visitor.add_to_visit(new_class.class_name(), new_class.header_path())
            ret.append(new_class)
    ret.append(visitor)
    return ret

def remove_dir(dir_path: Path) -> None:
    if dir_path.exists():
        for file in dir_path.iterdir():
            if file.is_dir():
                remove_dir(file)
            else:
                file.unlink()
        dir_path.rmdir()

if __name__ == "__main__":

    parser = ArgumentParser(prog='generator', description="generate program artifacts")
    parser.add_argument('--clean', '-c', 
                        action='store_true',
                        help="clean")
    args = parser.parse_args()

    generators = Path('.').resolve()/'generators'
    grammer_file = generators/'grammer'
    statement_file = generators/'statement'
    include_dir = Path('.').resolve()/'include'/'generated'
    source_dir = Path('.').resolve()/'source'/'generated'
    grammer_include_dir = Path('.').resolve()/'include'/'generated'/'expression'
    grammer_source_dir = Path('.').resolve()/'source'/'generated'/'expression'
    statement_include_dir = Path('.').resolve()/'include'/'generated'/'statement'
    statement_source_dir = Path('.').resolve()/'source'/'generated'/'statement'

    if args.clean:
        remove_dir(include_dir)
        remove_dir(source_dir)
        exit(0)

    if not include_dir.exists():
        include_dir.mkdir()
    if not source_dir.exists():
        source_dir.mkdir()
    if not grammer_include_dir.exists():
        grammer_include_dir.mkdir()
    if not grammer_source_dir.exists():
        grammer_source_dir.mkdir()
    if not statement_include_dir.exists():
        statement_include_dir.mkdir()
    if not statement_source_dir.exists():
        statement_source_dir.mkdir()

    grammer_update_time = grammer_file.stat().st_mtime
    for f in parse_grammer_file(grammer_file, grammer_include_dir, grammer_source_dir):
        if f.check_time(grammer_update_time):
            f.write()
    statement_update_time = statement_file.stat().st_mtime
    for f in parse_statement_file(statement_file, statement_include_dir, statement_source_dir):
        if f.check_time(statement_update_time):
            f.write()
    exit(0)