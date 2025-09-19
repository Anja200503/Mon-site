<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Optimisation de Coupe - Import Excel</title>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/xlsx/0.18.5/xlsx.full.min.js"></script>
    <style>
        * {
            box-sizing: border-box;
            margin: 0;
            padding: 0;
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
        }
        
        body {
            background-color: #f5f7f9;
            color: #333;
            line-height: 1.6;
            padding: 20px;
        }
        
        .container {
            max-width: 1200px;
            margin: 0 auto;
            background-color: white;
            border-radius: 10px;
            box-shadow: 0 0 20px rgba(0, 0, 0, 0.1);
            padding: 25px;
        }
        
        header {
            text-align: center;
            margin-bottom: 30px;
            padding-bottom: 20px;
            border-bottom: 1px solid #eaeaea;
        }
        
        h1 {
            color: #2c3e50;
            margin-bottom: 10px;
        }
        
        h2 {
            color: #3498db;
            margin: 25px 0 15px;
        }
        
        .description {
            color: #7f8c8d;
            max-width: 800px;
            margin: 0 auto;
        }
        
        .input-section {
            display: grid;
            grid-template-columns: 1fr 1fr;
            gap: 30px;
            margin-bottom: 30px;
        }
        
        @media (max-width: 768px) {
            .input-section {
                grid-template-columns: 1fr;
            }
        }
        
        .form-group {
            margin-bottom: 20px;
        }
        
        label {
            display: block;
            margin-bottom: 8px;
            font-weight: 600;
            color: #2c3e50;
        }
        
        input, button, select {
            padding: 12px 15px;
            border: 1px solid #ddd;
            border-radius: 5px;
            width: 100%;
            font-size: 16px;
        }
        
        button {
            background-color: #3498db;
            color: white;
            border: none;
            cursor: pointer;
            transition: background-color 0.3s;
            font-weight: 600;
        }
        
        button:hover {
            background-color: #2980b9;
        }
        
        .btn-secondary {
            background-color: #2ecc71;
        }
        
        .btn-secondary:hover {
            background-color: #27ae60;
        }
        
        .btn-danger {
            background-color: #e74c3c;
            width: auto;
        }
        
        .btn-danger:hover {
            background-color: #c0392b;
        }
        
        .excel-import {
            background-color: #e8f4fc;
            padding: 20px;
            border-radius: 8px;
            margin-bottom: 20px;
        }
        
        .file-upload {
            border: 2px dashed #3498db;
            padding: 20px;
            text-align: center;
            border-radius: 8px;
            margin-bottom: 15px;
            cursor: pointer;
            transition: background-color 0.3s;
        }
        
        .file-upload:hover {
            background-color: #d6eaf8;
        }
        
        .file-upload p {
            margin-top: 10px;
            color: #7f8c8d;
        }
        
        .cuts-list {
            margin-top: 15px;
            max-height: 300px;
            overflow-y: auto;
        }
        
        .cut-item {
            display: flex;
            justify-content: space-between;
            align-items: center;
            padding: 12px;
            background-color: #f8f9fa;
            border-radius: 5px;
            margin-bottom: 10px;
        }
        
        .cut-details {
            flex-grow: 1;
            display: flex;
            justify-content: space-between;
            align-items: center;
        }
        
        .cut-info {
            font-weight: 500;
        }
        
        .cut-quantity {
            background-color: #e8f4fc;
            padding: 5px 10px;
            border-radius: 15px;
            font-weight: bold;
            color: #3498db;
        }
        
        .input-row {
            display: flex;
            gap: 10px;
        }
        
        .input-row input {
            flex: 1;
        }
        
        .input-row button {
            width: auto;
        }
        
        .results-section {
            margin-top: 30px;
        }
        
        .optimization-result {
            margin-top: 20px;
            padding: 20px;
            background-color: #f8f9fa;
            border-radius: 5px;
        }
        
        .bar-result {
            margin-bottom: 20px;
            padding: 15px;
            background-color: #e8f4fc;
            border-radius: 5px;
            border-left: 5px solid #3498db;
        }
        
        .cuts-visualization {
            display: flex;
            align-items: center;
            margin-top: 10px;
            height: 40px;
            background-color: #e0e0e0;
            border-radius: 5px;
            overflow: hidden;
        }
        
        .cut-piece {
            height: 100%;
            display: flex;
            align-items: center;
            justify-content: center;
            color: white;
            font-weight: bold;
            font-size: 14px;
            transition: all 0.3s;
        }
        
        .cut-piece:hover {
            transform: scale(1.05);
            z-index: 2;
            box-shadow: 0 0 5px rgba(0,0,0,0.3);
        }
        
        .waste-piece {
            background-color: #e74c3c;
        }
        
        .stats {
            display: grid;
            grid-template-columns: repeat(3, 1fr);
            gap: 15px;
            margin-top: 25px;
        }
        
        .stat-box {
            text-align: center;
            padding: 15px;
            border-radius: 5px;
            background-color: #f8f9fa;
        }
        
        .stat-value {
            font-size: 24px;
            font-weight: bold;
            color: #2c3e50;
        }
        
        .stat-label {
            color: #7f8c8d;
        }
        
        .summary {
            margin-top: 30px;
            padding: 20px;
            background-color: #e8f4fc;
            border-radius: 5px;
        }
        
        .summary-item {
            display: flex;
            justify-content: space-between;
            padding: 8px 0;
            border-bottom: 1px solid #d1e7f7;
        }
        
        footer {
            text-align: center;
            margin-top: 40px;
            color: #7f8c8d;
            font-size: 14px;
        }
        
        .instructions {
            background-color: #fff8e1;
            padding: 15px;
            border-radius: 5px;
            margin: 20px 0;
            border-left: 5px solid #ffc107;
        }
        
        .instructions ul {
            margin-left: 20px;
            margin-top: 10px;
        }
        
        .instructions li {
            margin-bottom: 5px;
        }
        
        .excel-format {
            margin-top: 15px;
            padding: 15px;
            background-color: #f9f9f9;
            border-radius: 5px;
        }
        
        .excel-format h4 {
            margin-bottom: 10px;
            color: #2c3e50;
        }
        
        table {
            width: 100%;
            border-collapse: collapse;
            margin-top: 10px;
        }
        
        th, td {
            border: 1px solid #ddd;
            padding: 8px;
            text-align: left;
        }
        
        th {
            background-color: #f2f2f2;
        }
        
        .hidden {
            display: none;
        }
    </style>
</head>
<body>
    <div class="container">
        <header>
            <h1>Optimisation de Coupe de Barres en Aluminium</h1>
            <p class="description">
                Cet outil vous aide à optimiser la découpe de barres d'aluminium pour minimiser les chutes et réduire les coûts.
                Importez vos données depuis Excel ou saisissez-les manuellement.
            </p>
        </header>
        
        <div class="instructions">
            <h3>Comment utiliser cet outil :</h3>
            <ul>
                <li>Importez un fichier Excel avec les colonnes "Longueur" et "Quantité"</li>
                <li>Ou saisissez manuellement les longueurs et quantités nécessaires</li>
                <li>Entrez la longueur des barres standards que vous utilisez</li>
                <li>Cliquez sur "Optimiser" pour obtenir le plan de coupe optimal</li>
            </ul>
        </div>
        
        <div class="excel-import">
            <h2>Importation depuis Excel</h2>
            <div class="file-upload" id="file-upload">
                <input type="file" id="excel-file" accept=".xlsx, .xls" class="hidden">
                <label for="excel-file" style="cursor: pointer;">
                    <svg width="50" height="50" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg">
                        <path d="M14 2H6C4.9 2 4.01 2.9 4.01 4L4 20C4 21.1 4.89 22 5.99 22H18C19.1 22 20 21.1 20 20V8L14 2Z" fill="#3498db"/>
                        <path d="M16 18H8V16H16V18ZM16 14H8V12H16V14ZM13 9V3.5L18.5 9H13Z" fill="white"/>
                    </svg>
                    <p>Cliquez pour importer un fichier Excel</p>
                </label>
            </div>
            <div class="excel-format">
                <h4>Format attendu du fichier Excel :</h4>
                <table>
                    <thead>
                        <tr>
                            <th>Longueur (mm)</th>
                            <th>Quantité</th>
                        </tr>
                    </thead>
                    <tbody>
                        <tr>
                            <td>2500</td>
                            <td>4</td>
                        </tr>
                        <tr>
                            <td>1800</td>
                            <td>6</td>
                        </tr>
                        <tr>
                            <td>1200</td>
                            <td>8</td>
                        </tr>
                    </tbody>
                </table>
            </div>
        </div>
        
        <div class="input-section">
            <div class="bar-input">
                <h2>Paramètres des barres</h2>
                <div class="form-group">
                    <label for="bar-length">Longueur des barres standards (mm)</label>
                    <input type="number" id="bar-length" min="1" value="6000" placeholder="Longueur en mm">
                </div>
                
                <div class="form-group">
                    <label for="bar-quantity">Nombre maximum de barres disponibles</label>
                    <input type="number" id="bar-quantity" min="1" value="10" placeholder="Quantité">
                </div>
            </div>
            
            <div class="cuts-input">
                <h2>Coupes nécessaires</h2>
                <div class="form-group">
                    <label for="cut-length">Longueur de coupe (mm)</label>
                    <div class="input-row">
                        <input type="number" id="cut-length" min="1" placeholder="Longueur en mm">
                        <input type="number" id="cut-quantity" min="1" value="1" placeholder="Quantité" style="max-width: 100px;">
                        <button id="add-cut" class="btn-secondary">Ajouter</button>
                    </div>
                </div>
                
                <div class="form-group">
                    <label>Liste des coupes à effectuer</label>
                    <div class="cuts-list" id="cuts-list">
                        <!-- Les coupes ajoutées apparaîtront ici -->
                    </div>
                </div>
            </div>
        </div>
        
        <button id="optimize-btn">Optimiser la découpe</button>
        
        <div class="results-section" id="results-section" style="display: none;">
            <h2>Résultats de l'optimisation</h2>
            
            <div class="summary">
                <h3>Résumé de l'optimisation</h3>
                <div class="summary-item">
                    <span>Longueur des barres:</span>
                    <span id="summary-bar-length">6000 mm</span>
                </div>
                <div class="summary-item">
                    <span>Barres utilisées:</span>
                    <span id="summary-bars-used">0</span>
                </div>
                <div class="summary-item">
                    <span>Chute totale:</span>
                    <span id="summary-total-waste">0 mm</span>
                </div>
                <div class="summary-item">
                    <span>Pourcentage de chute:</span>
                    <span id="summary-waste-percent">0%</span>
                </div>
            </div>
            
            <h3>Plan de découpe détaillé</h3>
            <div class="optimization-result" id="optimization-result">
                <!-- Les résultats apparaîtront ici -->
            </div>
            
            <div class="stats">
                <div class="stat-box">
                    <div class="stat-value" id="total-bars">0</div>
                    <div class="stat-label">Barres utilisées</div>
                </div>
                <div class="stat-box">
                    <div class="stat-value" id="total-waste">0 mm</div>
                    <div class="stat-label">Chute totale</div>
                </div>
                <div class="stat-box">
                    <div class="stat-value" id="waste-percentage">0%</div>
                    <div class="stat-label">Pourcentage de chute</div>
                </div>
            </div>
        </div>
        
        <footer>
            <p>Outil d'optimisation de coupe de barres en aluminium | © 2023</p>
        </footer>
    </div>

    <script>
        document.addEventListener('DOMContentLoaded', function() {
            const cutsList = document.getElementById('cuts-list');
            const addCutBtn = document.getElementById('add-cut');
            const cutLengthInput = document.getElementById('cut-length');
            const cutQuantityInput = document.getElementById('cut-quantity');
            const optimizeBtn = document.getElementById('optimize-btn');
            const resultsSection = document.getElementById('results-section');
            const optimizationResult = document.getElementById('optimization-result');
            const totalBarsElement = document.getElementById('total-bars');
            const totalWasteElement = document.getElementById('total-waste');
            const wastePercentageElement = document.getElementById('waste-percentage');
            const excelFileInput = document.getElementById('excel-file');
            
            // Éléments de résumé
            const summaryBarLength = document.getElementById('summary-bar-length');
            const summaryBarsUsed = document.getElementById('summary-bars-used');
            const summaryTotalWaste = document.getElementById('summary-total-waste');
            const summaryWastePercent = document.getElementById('summary-waste-percent');
            
            let cuts = [];
            
            // Initialiser la liste des coupes
            updateCutsList();
            
            // Gérer l'import de fichier Excel
            excelFileInput.addEventListener('change', function(e) {
                const file = e.target.files[0];
                if (!file) return;
                
                const reader = new FileReader();
                reader.onload = function(e) {
                    const data = new Uint8Array(e.target.result);
                    const workbook = XLSX.read(data, { type: 'array' });
                    
                    // Supposer que la première feuille contient les données
                    const worksheet = workbook.Sheets[workbook.SheetNames[0]];
                    const jsonData = XLSX.utils.sheet_to_json(worksheet);
                    
                    // Traiter les données
                    processExcelData(jsonData);
                };
                reader.readAsArrayBuffer(file);
            });
            
            // Traiter les données Excel importées
            function processExcelData(data) {
                cuts = [];
                
                data.forEach(row => {
                    // Vérifier les noms de colonnes possibles
                    const length = row['Longueur'] || row['Longueur (mm)'] || row['LENGTH'] || row['Length'];
                    const quantity = row['Quantité'] || row['Quantite'] || row['Qty'] || row['QUANTITY'] || row['Quantity'];
                    
                    if (length && quantity) {
                        cuts.push({
                            length: parseInt(length),
                            quantity: parseInt(quantity)
                        });
                    }
                });
                
                if (cuts.length === 0) {
                    alert('Aucune donnée valide trouvée dans le fichier. Assurez-vous d\'avoir les colonnes "Longueur" et "Quantité".');
                    return;
                }
                
                updateCutsList();
                alert(`Données importées avec succès! ${cuts.length} types de coupes chargées.`);
            }
            
            // Ajouter une coupe à la liste
            addCutBtn.addEventListener('click', function() {
                const length = parseInt(cutLengthInput.value);
                const quantity = parseInt(cutQuantityInput.value);
                
                if (length && length > 0 && quantity && quantity > 0) {
                    cuts.push({ length, quantity });
                    updateCutsList();
                    cutLengthInput.value = '';
                    cutQuantityInput.value = '1';
                    cutLengthInput.focus();
                } else {
                    alert('Veuillez entrer une longueur et une quantité valides');
                }
            });
            
            // Mettre à jour l'affichage de la liste des coupes
            function updateCutsList() {
                cutsList.innerHTML = '';
                
                if (cuts.length === 0) {
                    cutsList.innerHTML = '<p style="padding: 10px; text-align: center; color: #7f8c8d;">Aucune coupe ajoutée</p>';
                    return;
                }
                
                cuts.forEach((cut, index) => {
                    const cutItem = document.createElement('div');
                    cutItem.className = 'cut-item';
                    cutItem.innerHTML = `
                        <div class="cut-details">
                            <span class="cut-info">${cut.length} mm</span>
                            <span class="cut-quantity">×${cut.quantity}</span>
                        </div>
                        <button class="btn-danger" data-index="${index}">×</button>
                    `;
                    cutsList.appendChild(cutItem);
                });
                
                // Ajouter des écouteurs d'événements pour les boutons de suppression
                document.querySelectorAll('.btn-danger').forEach(btn => {
                    btn.addEventListener('click', function() {
                        const index = parseInt(this.getAttribute('data-index'));
                        cuts.splice(index, 1);
                        updateCutsList();
                    });
                });
            }
            
            // Optimiser la découpe
            optimizeBtn.addEventListener('click', function() {
                const barLength = parseInt(document.getElementById('bar-length').value);
                const barQuantity = parseInt(document.getElementById('bar-quantity').value);
                
                if (!barLength || barLength <= 0) {
                    alert('Veuillez entrer une longueur de barre valide');
                    return;
                }
                
                if (cuts.length === 0) {
                    alert('Veuillez ajouter au moins une coupe');
                    return;
                }
                
                // Préparer la liste de toutes les coupes individuelles
                let allCuts = [];
                cuts.forEach(cut => {
                    for (let i = 0; i < cut.quantity; i++) {
                        allCuts.push(cut.length);
                    }
                });
                
                // Trier les coupes par ordre décroissant pour l'algorithme First-Fit Decreasing
                const sortedCuts = [...allCuts].sort((a, b) => b - a);
                
                // Appliquer l'algorithme First-Fit Decreasing
                const bars = [];
                let remainingBars = barQuantity;
                
                for (const cut of sortedCuts) {
                    let placed = false;
                    
                    // Essayer de placer la coupe dans une barre existante
                    for (const bar of bars) {
                        if (bar.remaining >= cut) {
                            bar.cuts.push(cut);
                            bar.remaining -= cut;
                            placed = true;
                            break;
                        }
                    }
                    
                    // Si non placée, créer une nouvelle barre si possible
                    if (!placed && remainingBars > 0) {
                        bars.push({
                            cuts: [cut],
                            remaining: barLength - cut
                        });
                        remainingBars--;
                    } else if (!placed) {
                        alert('Nombre de barres insuffisant pour effectuer toutes les coupes');
                        break;
                    }
                }
                
                // Afficher les résultats
                displayResults(bars, barLength);
            });
            
            // Afficher les résultats de l'optimisation
            function displayResults(bars, barLength) {
                optimizationResult.innerHTML = '';
                let totalWaste = 0;
                
                // Mettre à jour le résumé
                summaryBarLength.textContent = `${barLength} mm`;
                summaryBarsUsed.textContent = bars.length;
                
                bars.forEach((bar, index) => {
                    const barResult = document.createElement('div');
                    barResult.className = 'bar-result';
                    
                    // Calculer la chute pour cette barre
                    const waste = bar.remaining;
                    totalWaste += waste;
                    
                    // Créer la visualisation des coupes
                    let visualizationHtml = '<div class="cuts-visualization">';
                    bar.cuts.forEach(cut => {
                        const width = (cut / barLength) * 100;
                        const hue = Math.floor(Math.random() * 360);
                        visualizationHtml += `<div class="cut-piece" style="width: ${width}%; background-color: hsl(${hue}, 70%, 60%)">${cut} mm</div>`;
                    });
                    
                    if (waste > 0) {
                        const wasteWidth = (waste / barLength) * 100;
                        visualizationHtml += `<div class="cut-piece waste-piece" style="width: ${wasteWidth}%">${waste} mm</div>`;
                    }
                    
                    visualizationHtml += '</div>';
                    
                    barResult.innerHTML = `
                        <h4>Barre ${index + 1}</h4>
                        <p>Coupes: ${bar.cuts.join(' mm, ')} mm</p>
                        <p>Chute: ${waste} mm (${(waste/barLength*100).toFixed(1)}%)</p>
                        ${visualizationHtml}
                    `;
                    
                    optimizationResult.appendChild(barResult);
                });
                
                // Calculer les statistiques
                const totalBars = bars.length;
                const totalLength = totalBars * barLength;
                const wastePercentage = (totalWaste / totalLength * 100).toFixed(1);
                
                // Mettre à jour le résumé
                summaryTotalWaste.textContent = `${totalWaste} mm`;
                summaryWastePercent.textContent = `${wastePercentage}%`;
                
                // Afficher les statistiques
                totalBarsElement.textContent = totalBars;
                totalWasteElement.textContent = `${totalWaste} mm`;
                wastePercentageElement.textContent = `${wastePercentage}%`;
                
                // Afficher la section des résultats
                resultsSection.style.display = 'block';
                
                // Faire défiler jusqu'aux résultats
                resultsSection.scrollIntoView({ behavior: 'smooth' });
            }
        });
    </script>
</body>
</html>
