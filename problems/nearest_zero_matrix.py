#
#Finding Nearest Zero in a Matrix
#
#https://leetcode.com/submissions/detail/400599535/
#

import sys

def updateMatrixDFS(matrix, result_matrix, r, c, visited):
    #already zero
    print 'r : {}, c :{}'.format(r, c)
    if matrix[r][c] == 0:
        return matrix[r][c]
    #already visited
    if result_matrix[r][c] != -1:
        return result_matrix[r][c]
    else:
    #search nearest zero
        d = []
        if r > 0 and (r - 1, c) not in visited:
            visited.add((r - 1, c))
            d0 = 1 + updateMatrixDFS(matrix, result_matrix, r - 1, c, visited)
            visited.remove((r - 1, c))
            d.append(d0)
        if r < (len(matrix) - 1) and (r + 1, c) not in visited:
            visited.add((r + 1, c))
            d1 = 1 + updateMatrixDFS(matrix, result_matrix, r + 1, c, visited)
            visited.remove((r + 1, c))
            d.append(d1)
        if c > 0 and (r, c - 1) not in visited:
            visited.add((r, c - 1))
            d2 = 1 + updateMatrixDFS(matrix, result_matrix, r, c - 1, visited)
            visited.remove((r, c - 1))
            d.append(d2)
        if c < (len(matrix[0]) - 1) and (r, c + 1) not in visited:
            visited.add((r, c + 1))
            d3 = 1 + updateMatrixDFS(matrix, result_matrix, r, c + 1, visited)
            visited.remove((r, c + 1))
            d.append(d3)
        if len(d) > 0:
            return min(d)
        # all nodes were visited    
        return sys.maxsize

def updateMatrixBFS(matrix, r, c):
    if matrix[r][c] == 0:
        return matrix[r][c]
    visited = set()
    st = [ [r, c, 0 ] ]
    while len(st) > 0:
        sr, sc, d = st.pop(0)
        if matrix[sr][sc] == 0:
             return d
        visited.add((sr, sc))
        if sr > 0 and (sr - 1, sc) not in visited:
            st.append([sr - 1, sc, d + 1])
        if sr < (len(matrix) - 1) and (sr + 1, sc) not in visited:
            st.append([sr + 1, sc, d + 1])
        if sc > 0 and (sr, sc - 1) not in visited:
            st.append([sr, sc - 1, d + 1])
        if sc < (len(matrix[0]) - 1) and (sr, sc + 1) not in visited:
            st.append([sr, sc + 1, d + 1])
    return sys.maxsize

def updateMatrix(matrix):
    """
    :type matrix: List[List[int]]
    :rtype: List[List[int]]
    """
    rows = len(matrix)
    cols = len(matrix[0])
    result_matrix = [[]] * rows
    for r in range(rows):
        result_matrix[r] = [-1] * cols
    for r in result_matrix:
        print r
    visited = set()
    for r in range(rows): 
        for c in range(cols):
            result_matrix[r][c] = updateMatrixBFS(matrix, r, c)
            #result_matrix[r][c] = updateMatrixDFS(matrix, result_matrix, r, c, visited)
    return result_matrix

if __name__ ==  "__main__":
    matrix = [
                [0,0,0],
                [0,1,0],
                [0,0,0]
             ]
    result = updateMatrix(matrix)         
    for r in range(len(result)):
        print result[r]

    matrix = [
                [0,0,0],
                [0,1,0],
                [1,1,1]
             ]
    result = updateMatrix(matrix)         
    for r in range(len(result)):
        print result[r]

    matrix = [
                [0,0],
                [1,1]
             ]
    result = updateMatrix(matrix)         
    for r in range(len(result)):
        print result[r]

    matrix = [[1,1,0,0,1,0,0,1,1,0],[1,0,0,1,0,1,1,1,1,1],[1,1,1,0,0,1,1,1,1,0],[0,1,1,1,0,1,1,1,1,1],[0,0,1,1,1,1,1,1,1,0],[1,1,1,1,1,1,0,1,1,1],[0,1,1,1,1,1,1,0,0,1],[1,1,1,1,1,0,0,1,1,1],[0,1,0,1,1,0,1,1,1,1],[1,1,1,0,1,0,1,1,1,1]]

    result = updateMatrix(matrix)         
    for r in range(len(result)):
        print result[r]
    print '**'
    for r in range(len(matrix)):
        print matrix[r]
