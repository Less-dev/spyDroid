package net.spydroid.template.calculator.presentation

import androidx.compose.foundation.background
import androidx.compose.foundation.horizontalScroll
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.rememberScrollState
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.collectAsState
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.text.TextStyle
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.lifecycle.viewmodel.compose.viewModel
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.delay
import kotlinx.coroutines.launch
import net.spydroid.template.calculator.CONSTANTS
import net.spydroid.template.calculator.NUMBERS
import net.spydroid.template.calculator.OPERATIONS
import net.spydroid.template.calculator.components.IconNumber

@Composable
internal fun HomeScreen(homeViewModel: HomeViewModel = viewModel()) {

    val operation = homeViewModel.operation.collectAsState().value

    Box(
        modifier = Modifier
            .fillMaxSize()
            .padding(15.dp)
    ) {
        Column(modifier = Modifier.fillMaxSize(), verticalArrangement = Arrangement.Center) {
            TextFieldCalculator(text = operation)
            Spacer(modifier = Modifier.height(10.dp))
            NumbersCalculator(
                number = {
                    homeViewModel.addNumberToOperation(it)
                },
                operation = {
                    homeViewModel.addToOperation(it)
                }
            )
        }
    }
}

@Composable
private fun TextFieldCalculator(text: String) {
    val scrollState = rememberScrollState()

    LaunchedEffect(text) {
        this.launch(Dispatchers.IO) {
            delay(100)
            scrollState.scrollTo(scrollState.maxValue)
        }
    }

    Box(
        modifier = Modifier
            .fillMaxWidth(1f)
            .clip(RoundedCornerShape(15.dp))
            .height(60.dp)
            .background(color = Color.Gray.copy(alpha = 0.85f))
    ) {
        Text(
            text = text,
            style = TextStyle(
                fontSize = 25.sp,
                fontWeight = FontWeight.ExtraBold,
                color = if (text != CONSTANTS.MATH_ERROR) Color.White.copy(alpha = 0.85F) else Color.Red
            ),
            modifier = Modifier
                .align(Alignment.BottomEnd)
                .padding(15.dp)
                .horizontalScroll(scrollState)
        )
    }
}


@Composable
fun NumbersCalculator(number: (Int) -> Unit, operation: (String) -> Unit) {
    val colorOrange = Color(0xFFFFB300)

    Box(modifier = Modifier.fillMaxWidth(1F), contentAlignment = Alignment.Center) {
        Column {
            Row(
                modifier = Modifier.fillMaxWidth(1F),
                horizontalArrangement = Arrangement.SpaceBetween
            ) {
                IconNumber(number = OPERATIONS.C, color = Color.White.copy(alpha = 0.85F)) {
                    operation(OPERATIONS.C)
                }
                IconNumber(
                    number = OPERATIONS.DEL,
                    color = Color.White.copy(alpha = 0.85F),
                    fontSize = 35.5.sp
                ) {
                    operation(OPERATIONS.DEL)
                }
                IconNumber(number = OPERATIONS.PERCENT, color = Color.White.copy(alpha = 0.85F)) {
                    operation(OPERATIONS.PERCENT)
                }
                IconNumber(number = OPERATIONS.DIVIDER, color = colorOrange) {
                    operation(OPERATIONS.DIVIDER)
                }
            }

            Spacer(modifier = Modifier.height(10.dp))

            Row(
                modifier = Modifier.fillMaxWidth(1F),
                horizontalArrangement = Arrangement.SpaceBetween
            ) {
                IconNumber(number = NUMBERS.SEVEN) {
                    number(NUMBERS.SEVEN.toInt())
                }
                IconNumber(number = NUMBERS.EIGHT) {
                    number(NUMBERS.EIGHT.toInt())
                }
                IconNumber(number = NUMBERS.NINE) {
                    number(NUMBERS.NINE.toInt())
                }
                IconNumber(number = OPERATIONS.MULTIPLY, color = colorOrange) {
                    operation(OPERATIONS.MULTIPLY)
                }
            }

            Spacer(modifier = Modifier.height(10.dp))

            Row(
                modifier = Modifier.fillMaxWidth(1F),
                horizontalArrangement = Arrangement.SpaceBetween
            ) {
                IconNumber(number = NUMBERS.FOUR) {
                    number(NUMBERS.FOUR.toInt())
                }
                IconNumber(number = NUMBERS.FIVE) {
                    number(NUMBERS.FIVE.toInt())
                }
                IconNumber(number = NUMBERS.SIX) {
                    number(NUMBERS.SIX.toInt())
                }
                IconNumber(number = OPERATIONS.LESS, color = colorOrange) {
                    operation(OPERATIONS.LESS)
                }
            }

            Spacer(modifier = Modifier.height(10.dp))

            Row(
                modifier = Modifier.fillMaxWidth(1F),
                horizontalArrangement = Arrangement.SpaceBetween
            ) {
                IconNumber(number = NUMBERS.ONE) {
                    number(NUMBERS.ONE.toInt())
                }
                IconNumber(number = NUMBERS.TWO) {
                    number(NUMBERS.TWO.toInt())
                }
                IconNumber(number = NUMBERS.THREE) {
                    number(NUMBERS.THREE.toInt())
                }
                IconNumber(number = OPERATIONS.MORE, color = colorOrange) {
                    operation(OPERATIONS.MORE)
                }
            }

            Spacer(modifier = Modifier.height(10.dp))

            Row(
                modifier = Modifier.fillMaxWidth(1F),
                horizontalArrangement = Arrangement.SpaceBetween
            ) {
                IconNumber(number = NUMBERS.ZERO) {
                    number(NUMBERS.ZERO.toInt())
                }
                IconNumber(number = OPERATIONS.POINT) {
                    operation(OPERATIONS.POINT)
                }
                IconNumber(number = OPERATIONS.EQUAL, color = colorOrange) {
                    operation(OPERATIONS.EQUAL)
                }
            }
        }
    }
}