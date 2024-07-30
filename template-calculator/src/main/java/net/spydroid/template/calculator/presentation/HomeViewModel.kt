package net.spydroid.template.calculator.presentation

import android.util.Log
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.delay
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.launch
import net.objecthunter.exp4j.ExpressionBuilder
import net.spydroid.template.calculator.CONSTANTS
import net.spydroid.template.calculator.OPERATIONS

class HomeViewModel : ViewModel() {

    private val _operation = MutableStateFlow("0")
    val operation: StateFlow<String> = _operation

    private val _operationImp = MutableStateFlow("0")

    fun addToOperation(operation: String) =
        viewModelScope.launch(Dispatchers.IO) {
            when (operation) {
                OPERATIONS.C -> C()
                OPERATIONS.DEL -> DEL()
                OPERATIONS.PERCENT -> PERCENT()
                OPERATIONS.DIVIDER -> DIVIDER()
                OPERATIONS.EQUAL -> EQUAL()
                OPERATIONS.MULTIPLY -> MULTIPLY()
                else -> {
                    _operation.value += operation
                    _operationImp.value += operation
                }
            }
        }

    fun addNumberToOperation(number: Int) =
        viewModelScope.launch(Dispatchers.IO) {
            _operation.value += number
            _operationImp.value += number
        }

    private fun DEL() =
        viewModelScope.launch(Dispatchers.IO) {
            _operation.value = _operation.value.dropLast(1)
            _operationImp.value = _operationImp.value.dropLast(1)
        }

    private fun C() =
        viewModelScope.launch(Dispatchers.IO) {
            _operation.value = ""
            _operationImp.value = ""
        }

    private fun PERCENT() =
        viewModelScope.launch(Dispatchers.IO) {
            _operation.value += OPERATIONS.PERCENT
            _operationImp.value += OPERATIONS.PERCENT
        }

    private fun DIVIDER() =
        viewModelScope.launch(Dispatchers.IO) {
            _operation.value += OPERATIONS.DIVIDER
            _operationImp.value += "/"
        }

    private fun MULTIPLY() =
        viewModelScope.launch(Dispatchers.IO) {
            _operation.value += OPERATIONS.MULTIPLY
            _operationImp.value += "*"
        }

    private fun EQUAL() =
        viewModelScope.launch(Dispatchers.IO) {
            RESULT()
        }

    private fun RESULT() =
        viewModelScope.launch(Dispatchers.IO) {
            try {
                Log.d("PRUEA9", "EXPRESIÓN: ${_operationImp.value}")
                _operationImp.value = ExpressionBuilder(_operationImp.value).build().evaluate().toInt().toString()
                _operation.value = _operationImp.value
            } catch (e: Exception) {
                _operation.value = CONSTANTS.MATH_ERROR
                delay(1500)
                _operation.value = ""
                _operationImp.value = ""
            }

        }

}