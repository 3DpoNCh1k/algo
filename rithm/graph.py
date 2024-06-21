from pathlib import Path
import sys
import os

print(sys.path)
print(os.getcwd())

from rithm.source_files import *

from graphlib import TopologicalSorter, CycleError

# TODO: use env or config
ALGO_PATH = Path(".").absolute()

def get_algo_name(path):
    path = path.absolute()
    algo_path = path.relative_to(ALGO_PATH)
    # print(path, algo_path, ALGO_PATH)
    if algo_path.parts[0] == "algo":
        path_in_algo = Path(*algo_path.parts[1:])
        return str(path_in_algo)
    
    return str(algo_path)

class Node:
    def __init__(self, file):
        self.file = file
    
    def __repr__(self):
        return get_algo_name(self.file.path)
    

def create_graph(path):
    start_path = path.absolute()

    nodes = {}
    def get_or_create_node(path):
        assert path.is_absolute()
        if path not in nodes:
            nodes[path] = Node(CppFile(path))
        return nodes[path]
    
    graph = {}
    
    def traverse(path):
        current_node = get_or_create_node(path)
        if current_node in graph:
            return
        
        # if (len(graph)) >= 2:
        #     return

        print(f"traverse {path}")
        graph[current_node] = []
        for dependency_name in current_node.file.algo_dependencies:
            dependency_path = ALGO_PATH / dependency_name
            print(f"traverse: dependency_path = {dependency_path}")
            assert dependency_path.exists()
            assert dependency_path.is_file()
            dependency_node = get_or_create_node(dependency_path)
            graph[current_node].append(dependency_node)
            traverse(dependency_path)


    traverse(start_path)
    return graph
    # print(ALGO_PATH)
    # traverse(path.absolute())
    # print(graph)
    # for key in graph.keys():
    #     print(key, hash(key))
    
    # for value in graph.values():
    #     for key in value:
    #         print(key, hash(key))

    # print(len(graph))
    # ts = TopologicalSorter(graph)
    # to = tuple(ts.static_order())
    # print(len(to))
    # print(to)

    # print(hash(Node(CppFile(path.absolute()))))
    # print(hash(Node(CppFile(path.absolute()))))

    # class Dummy:
    #     def __init__(self, value):
    #         self.value = value


    # graph = {Dummy('A'): [Dummy('B')], Dummy('B'): [Dummy('C')]}
    # graph = {1: [2], 2: [1]}
    # ts = TopologicalSorter(graph)
    # to = tuple(ts.static_order())
    # print(to)
    # print(len(to))


def has_cycle(graph):
    try:
        tuple(TopologicalSorter(graph).static_order())
        return False, []
    except CycleError as e:
        return True, e.args[1]
    


