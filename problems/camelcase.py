import string

# Note: we can edit pattern not the query
def camelCaseMatchDFS(query, qpos, pattern, ppos):
    #pattern has remaining unmatched characters 
    if qpos >= len(query) and ppos < len(pattern):
        return False

    #all characters in pattern have been matched
    #check if query has any letters remaining which
    #can be something other than lower case here
    if ppos >= len(pattern):
        if qpos < len(query):
            for p in query[qpos:]:
                if p not in string.ascii_lowercase:
                    return False
        return True

    # try embedding characters 
    if pattern[ppos] == query[qpos]:
        return camelCaseMatchDFS(query, qpos + 1, pattern, ppos + 1)
    elif query[qpos] in string.ascii_lowercase:
        return camelCaseMatchDFS(query, qpos + 1, pattern, ppos)
    else:
        return False
    
def camelCaseMatchDoDFS(queries, pattern):
    result = []
    for q in queries:
        result.append(camelCaseMatchDFS(q, 0, pattern, 0))
    return result

if __name__ == "__main__":
    queries = ["FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"]
    pattern = "FB"
    print 'ans :{}'.format(camelCaseMatchDoDFS(queries, pattern))
    print 'exp :{}'.format([True,False,True,True,False])

    queries = ["FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"]
    pattern = "FoBa"
    print 'ans :{}'.format(camelCaseMatchDoDFS(queries, pattern))
    print 'exp :{}'.format([True,False,True,False,False])

    queries = ["FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"]
    pattern = "FoBaT"
    print 'ans :{}'.format(camelCaseMatchDoDFS(queries, pattern))
    print 'exp :{}'.format([False,True,False,False,False])

    queries = ["CompetitiveProgramming","CounterPick","ControlPanel"]
    pattern = "CooP"
    print 'ans :{}'.format(camelCaseMatchDoDFS(queries, pattern))
    print 'exp :{}'.format([False,False,True])
