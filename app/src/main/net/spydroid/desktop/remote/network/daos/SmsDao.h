#ifndef SMS_DAO_H
#define SMS_DAO_H

#include <string>
#include <vector>
#include "../api/ApiService.h"
#include "../../models/SmsHandler.h"


class SmsDao {
public:
    virtual ~SmsDao() = default;
    
    // Método que retorna un dispositivo basado en un alias
    virtual std::vector<SmsHandler> getSms(const std::string& alias) const = 0;
};

class SmsDaoImpl : public SmsDao {
public:
    SmsDaoImpl() = default;
    std::vector<SmsHandler> getSms(const std::string& alias) const override;
private:
    ApiService apiService;  // Instancia de ApiService manejada internamente
};

#endif // SMS_DAO_H