void itg_init()
{
    spi_set_confirm(ITG_ADR, ITG_SMPLRT_DIV, ITG_SMPLRT_DIV_V);
    spi_set_confirm(ITG_ADR, ITG_DLPF_FS, ITG_DLPF_FS_V);
    spi_set_confirm(ITG_ADR, ITG_PWR_MGM, ITG_PWR_MGM_V);
    spi_set_confirm(ITG_ADR, ITG_INT_CFG, ITG_INT_CFG_V);
}

