# R Dashboards and Projects

This folder contains interactive dashboards and data visualization projects created in R. The projects use Shiny, Flexdashboard, Leaflet, Plotly, ggplot2, and spatial data processing tools.

## Projects

### Congressional Activity Flexdashboard

An interactive Flexdashboard built with Shiny and Plotly. It explores legislative activity in the United States and includes:

- the number of bills passed over time by political party,
- relationships between voting behaviour, ideology, and legislative effectiveness,
- interactive charts for the 110th Congress,
- a state selector for comparing the total number of bills passed by state delegations.

**Main file:** `congressional-flexdashboard/dashboard.Rmd`

### Global GDP Growth Dashboard

A Shiny dashboard presenting global GDP growth by year on an interactive Leaflet map. The application includes:

- a year slider covering 2003–2023,
- a choropleth world map,
- country-level GDP growth popups,
- summary statistics for the selected year,
- custom CSS styling.

**Main files:**

- `gdp-growth-dashboard/app.R`
- `gdp-growth-dashboard/df_data.csv`
- `gdp-growth-dashboard/www/custom.css`

### Hurricane Wind Field Visualization

A custom ggplot2 extension for visualizing hurricane wind radii. The project:

- reads and prepares historical hurricane track data,
- converts quadrant-based wind radii into geographic polygons,
- defines a custom `StatHurricane` object with `ggproto`,
- implements a reusable `geom_hurricane()` layer,
- visualizes Hurricane Ike wind fields at different wind-speed thresholds.

**Main files:**

- `hurricane-geom/geom_hurricane.R`
- `hurricane-geom/ebtrk_atlc_1988_2015.txt`
- `hurricane-geom/ike_hurricane_compare.png`

## Technologies

- R
- Shiny
- Flexdashboard
- Plotly
- Leaflet
- ggplot2
- dplyr
- tidyr
- sf
- geosphere
- patchwork

## Running the Projects

### Flexdashboard

Open `dashboard.Rmd` in RStudio and select **Run Document**.

### Shiny GDP Dashboard

Open `app.R` in RStudio and select **Run App**. The `df_data.csv` file must remain in the same directory as `app.R`, while `custom.css` must be stored inside the `www` directory.

### Hurricane Visualization

Place `ebtrk_atlc_1988_2015.txt` in the same directory as `geom_hurricane.R`, then run the script in RStudio.