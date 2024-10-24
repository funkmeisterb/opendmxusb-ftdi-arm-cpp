#include <iostream>
#include <ftdi.h> // Linux
//#include <ftd2xx.h> // Windows

int main() {
    struct ftdi_context ftdi;
    int ret;
    int deviceIndex = 0; // assuming device index is 0

    // Initialize FTDI context
    ret = ftdi_init(&ftdi);
    if (ret < 0) {
        std::cerr << "Failed to initialize FTDI context" << std::endl;
        return 1;
    }
    std::cout << "FTDI context initialized successfully." << std::endl;

    // Open FTDI device
    ret = ftdi_usb_open(&ftdi, 0x403, 0x6001); // lsusb: ID 0403:6001 Future Technology Devices International, Ltd FT232 Serial (UART) IC
    if (ret < 0) {
        std::cerr << "Failed to open FTDI device" << std::endl;
        ftdi_deinit(&ftdi);
        return 1;
    }
    std::cout << "FTDI device opened successfully." << std::endl;

    // Device initialization
    ret = ftdi_usb_reset(&ftdi); // equivalent to FTD2XX.ResetDevice
    if (ret < 0) {
        std::cerr << "Failed to reset device" << std::endl;
        ftdi_usb_close(&ftdi);
        ftdi_deinit(&ftdi);
        return 1;
    }
    std::cout << "Device reset successfully." << std::endl;

    ret = ftdi_set_latency_timer(&ftdi, 12); // equivalent to FTD2XX.SetDivisor
    if (ret < 0) {
        std::cerr << "Failed to set latency timer" << std::endl;
        ftdi_usb_close(&ftdi);
        ftdi_deinit(&ftdi);
        return 1;
    }
    std::cout << "Latency timer set successfully." << std::endl;

    ret = ftdi_set_line_property(&ftdi, BITS_8, STOP_BIT_2, NONE); // equivalent to FTD2XX.SetDataCharacteristics
    if (ret < 0) {
        std::cerr << "Failed to set line property" << std::endl;
        ftdi_usb_close(&ftdi);
        ftdi_deinit(&ftdi);
        return 1;
    }
    std::cout << "Line property set successfully." << std::endl;

    ret = ftdi_setflowctrl(&ftdi, SIO_DISABLE_FLOW_CTRL); // equivalent to FTD2XX.SetFlowControl
    if (ret < 0) {
        std::cerr << "Failed to set flow control" << std::endl;
        ftdi_usb_close(&ftdi);
        ftdi_deinit(&ftdi);
        return 1;
    }
    std::cout << "Flow control set successfully." << std::endl;

    ret = ftdi_setdtr(&ftdi, 0); // equivalent to FTD2XX.ClrRts
    if (ret < 0) {
        std::cerr << "Failed to clear RTS" << std::endl;
        ftdi_usb_close(&ftdi);
        ftdi_deinit(&ftdi);
        return 1;
    }
    std::cout << "RTS cleared successfully." << std::endl;

    // Write 5 bytes to the serial port
    unsigned char bytes[] = { 0xFF, 0xFF, 0x00, 0xFF, 0x00 }; // Gain/Red/Green/Blue/White
    ret = ftdi_write_data(&ftdi, bytes, 5);
    if (ret < 0) {
        std::cerr << "Failed to write data" << std::endl;
        ftdi_usb_close(&ftdi);
        ftdi_deinit(&ftdi);
        return 1;
    }
    std::cout << "5 bytes written to serial port successfully." << std::endl;

    // Close FTDI device
    ftdi_usb_close(&ftdi);
    std::cout << "FTDI device closed successfully." << std::endl;

    ftdi_deinit(&ftdi);
    std::cout << "FTDI context deinitialized successfully." << std::endl;

    return 0;
}