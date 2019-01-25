from os import listdir
import serial

def getPortList():
	devs = listdir('/dev')
	ttyDevs = []
	for dev in devs:
		if 'tty.usbmodem' in dev:
			ttyDevs.append(dev)
	return ttyDevs

def getUart(port):
	try:
		return serial.Serial('/dev/%s' % port, 115200, timeout=1)
	except serial.serialutil.SerialException:
		return None

if __name__=='__main__':
	devs = getPortList()
	for dev in devs:
		print "%s" % dev
