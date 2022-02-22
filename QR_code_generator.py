#import modules
import qrcode
import image

def qr_code_generator():

    # Creating an instance of QRCode class
    qr = qrcode.QRCode(
    version = 2, # The version parameter is an integer from 1 to 40 that controls the size of the QR Code
    box_size = 10, # size of the box where qrcode will be displayed
    border = 5 # It is the white part of image --border in all 4 sides with white color
    ) 
    # Data to be encoded
    data ="https://www.youtube.com/"

    # Adding data to the instance 'qr'
    qr.add_data(data)

    # This method with (fit=True) ensures that the entire dimension of the QR Code is utilized, even if our input data could fit into less number of boxes.
    qr.make(fit = True)

    img = qr.make_image(fill = "black",back_color = "white")

    # Saving as an image file
    img.save("test.png")


qr_code_generator()
