import openpyxl


def writeToExcel(fileName, column, row):
    try:
         file = open(fileName, 'r')
    except IOError:
         print('file error')

    while True:
        value = file.readline()
        if not value:
            break
        spreadsheet[column + str(row)] = float(value)
        row += 1

    file.close()

# открываем таблицу
book = openpyxl.Workbook()
spreadsheet = book.active

# записываем из файлов в таблицу
spreadsheet['A1'] = 'size'
writeToExcel('numVertices.txt', 'A', 2)

spreadsheet['B1'] = 'Kuhn'
writeToExcel('kuhn.txt', 'B', 2)

spreadsheet['C1'] = 'Hopkroft-Karp'
writeToExcel('karp.txt', 'C', 2)


# сохраняем таблицу
book.save('graph.xlsx')
print('txt files have been parsed, spreadsheet is ready!')

