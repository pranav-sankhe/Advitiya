
fname = '/home/pranav/project_repositories/advitiya/elec_tasks/insystem_programming/scripts/led.hex'

in_file = open(fname, 'r')
out_file = open('out_hex_file','w')


while True:
    ch=in_file.read(1)
    if not ch: break
    out_file.write(ch)
    out_file.write(',')