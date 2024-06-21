import 'package:flutter/material.dart';
import 'package:flutter/services.dart';

void main() => runApp(CalculadoraIMCApp());

class CalculadoraIMCApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Calculadora IMC',
      theme: ThemeData(
        primarySwatch: Colors.blue,
        visualDensity: VisualDensity.adaptivePlatformDensity,
      ),
      home: CalculadoraIMCScreen(),
    );
  }
}

class CalculadoraIMCScreen extends StatefulWidget {
  @override
  _CalculadoraIMCScreenState createState() => _CalculadoraIMCScreenState();
}

class _CalculadoraIMCScreenState extends State<CalculadoraIMCScreen> {
  final TextEditingController weightController = TextEditingController();
  final TextEditingController heightController = TextEditingController();

  double? imc;
  String? imcResultado;
  String selectedGender = 'Masculino';
  String errorMessage = '';

  void calculateIMC() {
    final double weight = double.tryParse(weightController.text) ?? 0;
    final double height = (double.tryParse(heightController.text) ?? 0) / 100;

    if (weight <= 0 || height <= 0) {
      setState(() {
        errorMessage = "Peso e altura devem ser maiores que zero.";
      });
      return;
    }

    setState(() {
      errorMessage = '';
      if (selectedGender == 'Masculino') {
        imc = weight / (height * height);
      } else {
        imc = weight / (height * height);
      }

      if (imc! < 18.5) {
        imcResultado = "Abaixo do Peso";
      } else if (imc! < 25) {
        imcResultado = "Normal";
      } else if (imc! < 30) {
        imcResultado = "Sobrepeso";
      } else {
        imcResultado = "Obesidade";
      }
    });
  }

  void showIMCInfoDialog(BuildContext context) {
    showDialog(
      context: context,
      builder: (context) => AlertDialog(
        title: Text('Categorias de IMC'),
        content: Column(
          mainAxisSize: MainAxisSize.min,
          children: <Widget>[
            Text('Abaixo do Peso: IMC < 18.5'),
            SizedBox(height: 8),
            Text('Normal: IMC 18.5 - 24.9'),
            SizedBox(height: 8),
            Text('Sobrepeso: IMC 25 - 29.9'),
            SizedBox(height: 8),
            Text('Obesidade: IMC >= 30'),
          ],
        ),
        actions: <Widget>[
          TextButton(
            onPressed: () => Navigator.of(context).pop(),
            child: Text('Fechar'),
          ),
        ],
      ),
    );
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Row(
          children: [
            Text('Calculadora IMC'),
            IconButton(
              icon: Icon(Icons.info_outline),
              onPressed: () {
                showIMCInfoDialog(context);
              },
            ),
          ],
        ),
      ),
      body: Padding(
        padding: const EdgeInsets.all(16.0),
        child: Column(
          children: <Widget>[
            Row(
              mainAxisAlignment: MainAxisAlignment.center,
              children: [
                GestureDetector(
                  onTap: () {
                    setState(() {
                      selectedGender = 'Masculino';
                    });
                  },
                  child: GenderWidget(
                    gender: 'Masculino',
                    isSelected: selectedGender == 'Masculino',
                  ),
                ),
                SizedBox(width: 16),
                GestureDetector(
                  onTap: () {
                    setState(() {
                      selectedGender = 'Feminino';
                    });
                  },
                  child: GenderWidget(
                    gender: 'Feminino',
                    isSelected: selectedGender == 'Feminino',
                  ),
                ),
              ],
            ),
            SizedBox(height: 24),
            TextField(
              controller: weightController,
              keyboardType: TextInputType.number,
              decoration: InputDecoration(
                labelText: 'Seu peso (kg)',
                border: OutlineInputBorder(),
                errorText: errorMessage.isNotEmpty ? errorMessage : null,
              ),
              inputFormatters: [
                FilteringTextInputFormatter.allow(RegExp(r'^[1-9][0-9]*$')),
                LengthLimitingTextInputFormatter(3),
              ],
            ),
            SizedBox(height: 16),
            TextField(
              controller: heightController,
              keyboardType: TextInputType.number,
              decoration: InputDecoration(
                labelText: 'Sua altura (cm)',
                border: OutlineInputBorder(),
                errorText: errorMessage.isNotEmpty ? errorMessage : null,
              ),
              inputFormatters: [
                FilteringTextInputFormatter.allow(RegExp(r'^[1-9][0-9]*$')),
                LengthLimitingTextInputFormatter(3),
              ],
            ),
            SizedBox(height: 24),
            ElevatedButton(
              onPressed: calculateIMC,
              child: Text('Calcular IMC'),
            ),
            SizedBox(height: 24),
            if (imc != null)
              Column(
                children: [
                  Text(
                    'Seu IMC:',
                    style: TextStyle(fontSize: 24, fontWeight: FontWeight.bold),
                  ),
                  Text(
                    imc!.toStringAsFixed(1),
                    style: TextStyle(fontSize: 48, fontWeight: FontWeight.bold),
                  ),
                  Text(
                    imcResultado!,
                    style: TextStyle(fontSize: 24, color: Colors.grey[700]),
                  ),
                  SizedBox(height: 16),
                  TextButton(
                    onPressed: () {
                      setState(() {
                        imc = null;
                        imcResultado = null;
                        weightController.clear();
                        heightController.clear();
                      });
                    },
                    child: Text('Calcular Novamente'),
                  ),
                ],
              ),
          ],
        ),
      ),
    );
  }
}

class GenderWidget extends StatelessWidget {
  final String gender;
  final bool isSelected;

  const GenderWidget({
    Key? key,
    required this.gender,
    required this.isSelected,
  }) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return Column(
      children: [
        CircleAvatar(
          radius: 40,
          backgroundColor: isSelected
              ? (gender == 'Masculino' ? Colors.blue : Colors.pink[200])
              : Colors.grey[300],
          child: Icon(
            gender == 'Masculino' ? Icons.male : Icons.female,
            size: 40,
            color: Colors.white,
          ),
        ),
        SizedBox(height: 8),
        Text(
          gender,
          style: TextStyle(
            fontSize: 18,
            fontWeight: FontWeight.bold,
            color: isSelected ? Colors.black : Colors.grey,
          ),
        ),
      ],
    );
  }
}
