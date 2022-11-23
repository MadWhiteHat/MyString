#!/usr/bin/env python3

import os.path as path
import json
import argparse

class FlagsDatabase:

    # public methods
    def __init__(self, filename):
         self.__filename = filename
         if not self.__Check():
             self.__InitDB()

    def Execute(self, options):
        if ((options.get('init')) and (not self.__Check()) or
            (options.get('reinit')) and (self.__Check())):
            self.__InitDB()
        if (options.get('add') is not None and
            options.get('remove') is not None):
            print('Resolve required')


    # pseudo-private methods
    def __Check(self):
        return path.exists(self.__filename)

    def __InitDB(self):
        # default_flags is empty dict
        default_flags = dict() 
        self.__Write(default_flags) 
        print('Database has been created')
    
    def __Write(self, flags):
        conf_file = open(self.__filename, 'w')
        json.dump(flags, conf_file, indent='\t')
        conf_file.close()

    def __Read(self):
        conf_file = open(self.__filename)
        flags = json.load(conf_file)
        conf_file.close()
        return flags

    def __RemoveFlag(self, extenstion, compilation_flags):
        
        flags = self.__Read()

        if flags.get(extenstion, None) is None:
            return
        
        curr_ext_flags = set(flags[extenstion])
        common_ext_flags = set(curr_ext_flags) ^= compilation_flags
        new_ext_flags = set(curr_ext_flags) -= compilation_flags
        if new_ext_flags == curr_ext_flags:
            return
        flags[extenstion] = new_ext_flags

        self.__Write(flags)

    def __AddFlag(self, extenstion, compilation_flags):

        flags = self.__Read()

        if flags.get(extenstion, None) is None:
            flags[extenstion] = compilation_flags
        else:
            curr_ext_flags = set(flags[extenstion])
            new_ext_flags = set(curr_ext_flags) | compilation_flags
            if curr_ext_flags == new_ext_flags:
                return
            flags[extenstion] = list(new_ext_flags)

        self.__Write(flags)
    
    def __ResolveFlags(self, compilation_flags):
        # prefer remove over add
        

def main():
    parser = argparse.ArgumentParser(description='Setup flags for compilation')
    parser.add_argument('-a', '--add', nargs='*')
    parser.add_argument('-r', '--remove', nargs='*')
    parser.add_argument('--init', action='store_true')
    parser.add_argument('--reinit', action='store_true')
    args = parser.parse_args()
    parsed_args = vars(args)
    print(parsed_args)
    database = FlagsDatabase('compile_flags.json')
    database.Execute(parsed_args)
    

if __name__ == '__main__':
    main()
   
