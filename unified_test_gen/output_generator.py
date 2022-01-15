def generate_output(container, sorted_container):
    lines_to_write = []
    lines_to_write.append(f'Container size: {str(len(container))}\n')
    if not len(container):
        return lines_to_write
    lines_to_write.append('INITIAL ORDER:\n')
    if not len(container):
        lines_to_write.append('')
    for element in container:
        lines_to_write.append(element[1])
        lines_to_write.append('')
    lines_to_write.append('SORTED:\n')
    for element in sorted_container:
        lines_to_write.append(element[1])
        lines_to_write.append('')
    if not len(sorted_container):
        lines_to_write.append('\n')
    return lines_to_write
